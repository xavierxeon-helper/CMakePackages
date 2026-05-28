#include "MultimediaVideoWriter.h"

#include <QDir>
#include <QMediaFormat>
#include <QUrl>

#include "../MultimediaCamera.h"

const uint64_t Multimedia::VideoWriter::maxVideoSizeInBytes = 256 * 1024 * 1024; // 256 MB video

Multimedia::VideoWriter::VideoWriter(QObject* parent, Camera* camera)
   : QMediaCaptureSession(parent)
   , setupFunction()
   , path()
   , size(640, 320)
   , fps(60)
   , ratio(10)
   , imageCapture(nullptr)
   , captureTimer(nullptr)
   , videoInput(nullptr)
   , recorder(nullptr)
   , frameSizeInBytes(0)
   , frameCount(0)
{
   // capture
   imageCapture = new QImageCapture(this);
   connect(imageCapture, &QImageCapture::imageAvailable, this, &VideoWriter::imageAvailable);
   camera->setImageCapture(imageCapture);

   captureTimer = new QTimer(this);
   connect(captureTimer, &QTimer::timeout, imageCapture, &QImageCapture::capture);

   // input
   videoInput = new QVideoFrameInput(this);
   setVideoFrameInput(videoInput);

   // recored
   recorder = new QMediaRecorder(this);
   recorder->setQuality(QMediaRecorder::NormalQuality);
   recorder->setEncodingMode(QMediaRecorder::ConstantQualityEncoding);

   QMediaFormat mf(QMediaFormat::MPEG4);
   mf.setVideoCodec(QMediaFormat::VideoCodec::H265);

   recorder->setMediaFormat(mf);

   //qDebug() << mf.supportedFileFormats(QMediaFormat::Encode);
   //qDebug() << mf.supportedVideoCodecs(QMediaFormat::Encode);

   setRecorder(recorder);
}

Multimedia::VideoWriter::~VideoWriter()
{
   stop();
}

void Multimedia::VideoWriter::setPath(const QString& newPath)
{
   path = newPath;
}

void Multimedia::VideoWriter::setSize(const QSize& newSize)
{
   size = newSize;
}

void Multimedia::VideoWriter::setFps(int newFps)
{
   fps = newFps;
}

void Multimedia::VideoWriter::setRatio(int newRatio)
{
   ratio = newRatio;
}

void Multimedia::VideoWriter::start()
{
   if (setupFunction)
      setupFunction();

   if (path.isEmpty())
      return;

   QDir().mkpath(path);

   const QDateTime now = QDateTime::currentDateTime();
   const QString fileName = path + "/" + now.toString("yyyyMMdd_hhmmss") + ".mp4";
   recorder->setOutputLocation(QUrl::fromLocalFile(fileName));

   recorder->setVideoResolution(size);
   recorder->setVideoFrameRate(fps);

   frameSizeInBytes = fps * size.width() * size.height() * 4;
   frameSizeInBytes /= 16 * 1024;
   frameCount = 0;

   recorder->record();

   if (QMediaRecorder::NoError != recorder->error())
   {
      qWarning() << __FUNCTION__ << "video" << fileName << "not open:" << recorder->errorString();
      stop();
   }
   else
   {
      const double intervall = 1000.0 * ratio / fps;
      captureTimer->start(intervall);
   }
}

void Multimedia::VideoWriter::stop()
{
   recorder->stop();
   captureTimer->stop();
}

bool Multimedia::VideoWriter::active() const
{
   //return captureTimer->isActive();
   const bool isRecording = (recorder->recorderState() == QMediaRecorder::RecordingState);
   return isRecording;
}

void Multimedia::VideoWriter::imageAvailable(int id, const QVideoFrame& frame)
{
   Q_UNUSED(id)

   frameCount++;

   const uint64_t videoSizeInBytes = frameCount * frameSizeInBytes;
   const double percentage = videoSizeInBytes * 100.0 / (double)maxVideoSizeInBytes;
   emit progress(static_cast<uint8_t>(percentage), videoSizeInBytes);

   const qint64 frameTime = 1000 * 1000 / recorder->videoFrameRate();
   const qint64 startTime = frameCount * frameTime;
   const qint64 endTime = (frameCount + 1) * frameTime;
   //qDebug() << startTime << frame.startTime();

   QVideoFrame localFrame(frame);
   localFrame.setStartTime(startTime);
   localFrame.setEndTime(endTime);
   videoInput->sendVideoFrame(localFrame);

   if (maxVideoSizeInBytes <= videoSizeInBytes)
   {
      stop();
      start();
   }
}
