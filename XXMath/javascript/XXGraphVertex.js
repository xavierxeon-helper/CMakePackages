/**
 * XXGraphVertex - Graph vertex representation
 * JavaScript translation of XX::Graph::Vertex class
 */

class XXGraphVertex
{
   /**
    * Create a graph vertex
    * @param {string} name - Vertex name (default empty string)
    */
   constructor ( name = "" )
   {
      this.name = name;
   }

   /**
    * Get vertex name
    * @returns {string} Vertex name
    */
   getName()
   {
      return this.name;
   }

   /**
    * Set vertex name
    * @param {string} name - New vertex name
    */
   setName( name )
   {
      this.name = name;
   }

   /**
    * String representation of vertex
    * @returns {string} String representation
    */
   toString()
   {
      return `Vertex[${this.name}]`;
   }

   /**
    * Check equality with another vertex
    * @param {XXGraphVertex} other - Other vertex
    * @returns {boolean} True if vertices are equal
    */
   equals( other )
   {
      return this.name === other.name;
   }

   /**
    * Create a copy of this vertex
    * @returns {XXGraphVertex} Copy of this vertex
    */
   clone()
   {
      return new XXGraphVertex( this.name );
   }
}

export default XXGraphVertex;