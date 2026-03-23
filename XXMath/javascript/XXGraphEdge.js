import XXGraphVertex from './XXGraphVertex.js';

/**
 * XXGraphEdge - Graph edge representation
 * JavaScript translation of XX::Graph::Edge class
 * An edge can be directed or undirected, depending on the weights
 */

class XXGraphEdge
{
   static invalidWeight = Number.NaN;

   /**
    * Create a graph edge
    * @param {XXGraphVertex} vertexA - First vertex (default null)
    * @param {XXGraphVertex} vertexB - Second vertex (default null)
    * @param {number} weightForward - Forward weight (default 1.0)
    * @param {number} weightBackward - Backward weight (default NaN for directed edge)
    */
   constructor ( vertexA = null, vertexB = null, weightForward = 1.0, weightBackward = XXGraphEdge.invalidWeight )
   {
      this.vertexA = vertexA;
      this.vertexB = vertexB;
      this.weightForward = weightForward;
      this.weightBackward = weightBackward;
   }

   /**
    * Get forward weight
    * @returns {number} Forward weight
    */
   getForwardWeight()
   {
      return this.weightForward;
   }

   /**
    * Set forward weight
    * @param {number} weight - Forward weight
    */
   setForwardWeight( weight )
   {
      this.weightForward = weight;
   }

   /**
    * Get backward weight
    * @returns {number} Backward weight
    */
   getBackwardWeight()
   {
      return this.weightBackward;
   }

   /**
    * Set backward weight
    * @param {number} weight - Backward weight
    */
   setBackwardWeight( weight )
   {
      this.weightBackward = weight;
   }

   /**
    * Check if edge has forward link
    * @returns {boolean} True if has forward link
    */
   hasForwardLink()
   {
      return !Number.isNaN( this.getForwardWeight() );
   }

   /**
    * Check if edge has backward link
    * @returns {boolean} True if has backward link
    */
   hasBackwardLink()
   {
      return !Number.isNaN( this.getBackwardWeight() );
   }

   /**
    * Check if edge links to a specific vertex
    * @param {XXGraphVertex} vertex - Vertex to check
    * @returns {boolean} True if edge links to the vertex
    */
   linksVertex( vertex )
   {
      return vertex === this.vertexA || vertex === this.vertexB;
   }

   /**
    * Get first vertex
    * @returns {XXGraphVertex} First vertex
    */
   getVertexA()
   {
      return this.vertexA;
   }

   /**
    * Get second vertex
    * @returns {XXGraphVertex} Second vertex
    */
   getVertexB()
   {
      return this.vertexB;
   }

   /**
    * Set first vertex
    * @param {XXGraphVertex} vertex - New first vertex
    */
   setVertexA( vertex )
   {
      this.vertexA = vertex;
   }

   /**
    * Set second vertex
    * @param {XXGraphVertex} vertex - New second vertex
    */
   setVertexB( vertex )
   {
      this.vertexB = vertex;
   }

   /**
    * Check if edge is bidirectional (undirected)
    * @returns {boolean} True if edge is bidirectional
    */
   isBidirectional()
   {
      return this.hasForwardLink() && this.hasBackwardLink();
   }

   /**
    * Check if edge is directed
    * @returns {boolean} True if edge is directed
    */
   isDirected()
   {
      return !this.isBidirectional();
   }

   /**
    * Get the other vertex connected by this edge
    * @param {XXGraphVertex} vertex - One vertex of the edge
    * @returns {XXGraphVertex|null} The other vertex, or null if vertex is not part of this edge
    */
   getOtherVertex( vertex )
   {
      if ( vertex === this.vertexA )
      {
         return this.vertexB;
      } else if ( vertex === this.vertexB )
      {
         return this.vertexA;
      }
      return null;
   }

   /**
    * Get weight from one vertex to another
    * @param {XXGraphVertex} fromVertex - Source vertex
    * @param {XXGraphVertex} toVertex - Target vertex
    * @returns {number} Weight or NaN if path not available
    */
   getWeight( fromVertex, toVertex )
   {
      if ( fromVertex === this.vertexA && toVertex === this.vertexB )
      {
         return this.weightForward;
      } else if ( fromVertex === this.vertexB && toVertex === this.vertexA )
      {
         return this.weightBackward;
      }
      return Number.NaN;
   }

   /**
    * String representation of edge
    * @returns {string} String representation
    */
   toString()
   {
      const aName = this.vertexA ? this.vertexA.getName() : 'null';
      const bName = this.vertexB ? this.vertexB.getName() : 'null';
      const forward = this.hasForwardLink() ? this.weightForward : 'none';
      const backward = this.hasBackwardLink() ? this.weightBackward : 'none';

      return `Edge[${aName} -> ${bName}: forward=${forward}, backward=${backward}]`;
   }

   /**
    * Check equality with another edge
    * @param {XXGraphEdge} other - Other edge
    * @returns {boolean} True if edges are equal
    */
   equals( other )
   {
      return this.vertexA === other.vertexA &&
         this.vertexB === other.vertexB &&
         this.weightForward === other.weightForward &&
         this.weightBackward === other.weightBackward;
   }

   /**
    * Create a copy of this edge
    * @returns {XXGraphEdge} Copy of this edge
    */
   clone()
   {
      return new XXGraphEdge( this.vertexA, this.vertexB, this.weightForward, this.weightBackward );
   }
}

export default XXGraphEdge;