#include "GraphVertex.h"

Graph::Vertex::Vertex(const QString& name)
   : name(name)
{
}

const QString& Graph::Vertex::getName() const
{
   return name;
}
