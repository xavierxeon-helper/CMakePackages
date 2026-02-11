#ifndef DiscreteMathsVertexH
#define DiscreteMathsVertexH

#include "XXGraphExportDef.h"

#include <QString>

#include "XXGraph.h"

class XXGRAPH_DECLSPEC Graph::Vertex
{
public:
   Vertex(const QString& name = QString());

public:
   const QString& getName() const;

protected:
   QString name;
};

#endif // NOT GraphAbstractVertexH
