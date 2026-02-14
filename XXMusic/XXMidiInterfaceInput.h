#ifndef XXMidiInterfaceInputH
#define XXMidiInterfaceInputH

#include "XXMidiParser.h"
#include "XXMusicExportDef.h"

namespace XX
{
   namespace Midi
   {
      namespace Interface
      {
         class Output;

         //! @brief midi input
         //! @ingroup XXMusic

         class XXMUSIC_DECLSPEC Input : public Parser
         {
         public:
            Input();
            virtual ~Input();

         public:
            virtual void open();
            virtual void close();
            virtual bool isOpen() const;

            void addPassThroughInterface(Interface::Output* passthrough);

         protected:
            QList<Interface::Output*> passthroughList;
         };
      } // namespace Interface
   } // namespace Midi
} // namespace XX

#endif // NOT XXMidiInterfaceInputH
