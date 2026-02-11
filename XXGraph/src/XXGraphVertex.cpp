#include "XXGraphVertex.h"

XX::Graph::Vertex::Vertex(const QString& name)
   : name(name)
{
}

const QString& XX::Graph::Vertex::getName() const
{
   return name;
}
