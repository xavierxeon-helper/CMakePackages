#ifndef DiscreteMathsVertexH
#define DiscreteMathsVertexH

#include "WaToolsGraphExportDef.h"

#include <QString>

#include "Graph.h"

class WATOOLSGRAPH_DECLSPEC Graph::Vertex
{
public:
   Vertex(const QString& name = QString());

public:
   const QString& getName() const;

protected:
   QString name;
};

#endif // NOT GraphAbstractVertexH
