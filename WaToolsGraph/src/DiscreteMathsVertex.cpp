#include "DiscreteMathsVertex.h"

DiscreteMaths::Vertex::Vertex(const QString& name)
   : name(name)
{
}

const QString& DiscreteMaths::Vertex::getName() const
{
   return name;
}
