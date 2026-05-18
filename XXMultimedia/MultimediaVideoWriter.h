#ifndef MultimediaVideoWriterH
#define MultimediaVideoWriterH

#include "XXMultimediaExportDef.h"
#include <QMediaCaptureSession>

#include <QImageCapture>
#include <QMediaRecorder>
#include <QTimer>
#include <QVideoFrameInput>

namespace Multimedia
{
   class Camera;

   //! @brief write video files from a camera
   //! @ingroup XXMultimedia

   class XXMULTIMEDIA_DECLSPEC VideoWriter : public QMediaCaptureSession
   {
      Q_OBJECT

   public:
      using SetupFunction = std::function<void()>;

   public:
      VideoWriter(QObject* parent, Camera* camera);
      ~VideoWriter();

   signals:
      void progress(uint8_t percentage, const uint64_t& videoSizeInBytes);

   public:
      template <typename ClassType>
      void registerSetupFunction(ClassType* instance, void (ClassType::*function)());

      void setPath(const QString& newPath);
      void setSize(const QSize& newSize);
      void setFps(int newFps);
      void setRatio(int newRatio);

      void start();
      void stop();
      bool active() const;

   private:
      void imageAvailable(int id, const QVideoFrame& frame);

   private:
      SetupFunction setupFunction;
      //
      QString path;
      QSize size;
      int fps;
      int ratio;

      // capture
      QImageCapture* imageCapture;
      QTimer* captureTimer;
      QVideoFrameInput* videoInput;
      QMediaRecorder* recorder;

      // output size limit
      uint64_t frameSizeInBytes;
      uint64_t frameCount;
      static const uint64_t maxVideoSizeInBytes;
   };
} // namespace Multimedia

#ifndef MultimediaVideoWriterHPP
#include "MultimediaVideoWriter.hpp"
#endif // NOT MultimediaVideoWriterHPP

#endif // NOT MultimediaVideoWriterH
