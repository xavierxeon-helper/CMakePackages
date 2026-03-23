import XXGraphVertex from './XXGraphVertex.js';
import XXGraphEdge from './XXGraphEdge.js';

/**
 * XXGraph - Graph data structure representation
 * JavaScript translation of XX::Graph class
 * Fill with vertices and edges, then use algorithms to process the graph data
 */

class XXGraph
{
   /**
    * Create a new graph
    */
   constructor ()
   {
      this.vertexList = [];
      this.edgeList = [];
   }

   /**
    * Add a vertex to the graph
    * @param {XXGraphVertex} vertex - Vertex to add
    * @returns {number} Index of the added vertex, or -1 if already exists
    */
   addVertex( vertex )
   {
      if ( this.vertexList.includes( vertex ) )
      {
         return -1;
      }

      this.vertexList.push( vertex );
      return this.vertexList.length - 1;
   }

   /**
    * Remove a vertex from the graph
    * @param {XXGraphVertex} vertex - Vertex to remove
    * @param {boolean} deleteVertex - Whether to delete the vertex object (not applicable in JS, kept for API compatibility)
    * @returns {boolean} True if vertex was removed
    */
   removeVertex( vertex, deleteVertex = false )
   {
      const index = this.vertexList.indexOf( vertex );
      if ( index === -1 )
      {
         return false;
      }

      this.vertexList.splice( index, 1 );

      // Remove all edges that link to this vertex
      const edgesToRemove = [];
      for ( const edge of this.edgeList )
      {
         if ( edge.linksVertex( vertex ) )
         {
            edgesToRemove.push( edge );
         }
      }

      for ( const edge of edgesToRemove )
      {
         this.removeEdge( edge );
      }

      return true;
   }

   /**
    * Get the index of a vertex
    * @param {XXGraphVertex} vertex - Vertex to find
    * @returns {number} Index of vertex, or -1 if not found
    */
   vertexIndex( vertex )
   {
      return this.vertexList.indexOf( vertex );
   }

   /**
    * Get the number of vertices in the graph
    * @returns {number} Number of vertices
    */
   vertexCount()
   {
      return this.vertexList.length;
   }

   /**
    * Get vertex by index
    * @param {number} vertexIndex - Index of vertex
    * @returns {XXGraphVertex|null} Vertex at index, or null if invalid index
    */
   getVertex( vertexIndex )
   {
      if ( vertexIndex < 0 || vertexIndex >= this.vertexList.length )
      {
         return null;
      }

      return this.vertexList[ vertexIndex ];
   }

   /**
    * Find vertex by name
    * @param {string} name - Name of vertex to find
    * @returns {XXGraphVertex|null} Vertex with the given name, or null if not found
    */
   findVertexByName( name )
   {
      for ( const vertex of this.vertexList )
      {
         if ( vertex.getName() === name )
         {
            return vertex;
         }
      }

      return null;
   }

   /**
    * Get all vertices
    * @returns {XXGraphVertex[]} Array of all vertices
    */
   getVertices()
   {
      return [ ...this.vertexList ]; // Return a copy
   }

   /**
    * Add an edge to the graph
    * @param {XXGraphEdge} edge - Edge to add
    * @returns {number} Index of the added edge, or -1 if already exists
    */
   addEdge( edge )
   {
      if ( this.edgeList.includes( edge ) )
      {
         return -1;
      }

      this.edgeList.push( edge );
      return this.edgeList.length - 1;
   }

   /**
    * Remove an edge from the graph
    * @param {XXGraphEdge} edge - Edge to remove
    * @param {boolean} deleteEdge - Whether to delete the edge object (not applicable in JS, kept for API compatibility)
    * @returns {boolean} True if edge was removed
    */
   removeEdge( edge, deleteEdge = false )
   {
      const index = this.edgeList.indexOf( edge );
      if ( index === -1 )
      {
         return false;
      }

      this.edgeList.splice( index, 1 );
      return true;
   }

   /**
    * Get the index of an edge
    * @param {XXGraphEdge} edge - Edge to find
    * @returns {number} Index of edge, or -1 if not found
    */
   edgeIndex( edge )
   {
      return this.edgeList.indexOf( edge );
   }

   /**
    * Get the number of edges in the graph
    * @returns {number} Number of edges
    */
   edgeCount()
   {
      return this.edgeList.length;
   }

   /**
    * Get edge by index
    * @param {number} edgeIndex - Index of edge
    * @returns {XXGraphEdge|null} Edge at index, or null if invalid index
    */
   getEdge( edgeIndex )
   {
      if ( edgeIndex < 0 || edgeIndex >= this.edgeList.length )
      {
         return null;
      }

      return this.edgeList[ edgeIndex ];
   }

   /**
    * Find edge index by vertices
    * @param {XXGraphVertex} vertexA - First vertex
    * @param {XXGraphVertex} vertexB - Second vertex
    * @returns {number} Index of edge connecting the vertices, or -1 if not found
    */
   findEdgeIndex( vertexA, vertexB )
   {
      for ( let edgeIndex = 0; edgeIndex < this.edgeList.length; edgeIndex++ )
      {
         const edge = this.edgeList[ edgeIndex ];
         if ( edge.getVertexA() === vertexA && edge.getVertexB() === vertexB )
         {
            return edgeIndex;
         }
      }

      return -1;
   }

   /**
    * Find edge by vertices
    * @param {XXGraphVertex} vertexA - First vertex
    * @param {XXGraphVertex} vertexB - Second vertex
    * @returns {XXGraphEdge|null} Edge connecting the vertices, or null if not found
    */
   findEdge( vertexA, vertexB )
   {
      const index = this.findEdgeIndex( vertexA, vertexB );
      return index !== -1 ? this.edgeList[ index ] : null;
   }

   /**
    * Get all edges
    * @returns {XXGraphEdge[]} Array of all edges
    */
   getEdges()
   {
      return [ ...this.edgeList ]; // Return a copy
   }

   /**
    * Get all edges connected to a vertex
    * @param {XXGraphVertex} vertex - Vertex to find edges for
    * @returns {XXGraphEdge[]} Array of edges connected to the vertex
    */
   getVertexEdges( vertex )
   {
      const edges = [];
      for ( const edge of this.edgeList )
      {
         if ( edge.linksVertex( vertex ) )
         {
            edges.push( edge );
         }
      }
      return edges;
   }

   /**
    * Get all neighbors of a vertex
    * @param {XXGraphVertex} vertex - Vertex to find neighbors for
    * @returns {XXGraphVertex[]} Array of neighboring vertices
    */
   getNeighbors( vertex )
   {
      const neighbors = [];
      for ( const edge of this.edgeList )
      {
         if ( edge.getVertexA() === vertex )
         {
            neighbors.push( edge.getVertexB() );
         } else if ( edge.getVertexB() === vertex && edge.hasBackwardLink() )
         {
            neighbors.push( edge.getVertexA() );
         }
      }
      return neighbors;
   }

   /**
    * Clear all vertices and edges from the graph
    * @param {boolean} deleteAll - Whether to delete objects (not applicable in JS, kept for API compatibility)
    */
   clear( deleteAll = false )
   {
      this.vertexList = [];
      this.edgeList = [];
   }

   /**
    * Check if the graph is empty
    * @returns {boolean} True if graph has no vertices or edges
    */
   isEmpty()
   {
      return this.vertexList.length === 0 && this.edgeList.length === 0;
   }

   /**
    * Check if two vertices are connected by an edge
    * @param {XXGraphVertex} vertexA - First vertex
    * @param {XXGraphVertex} vertexB - Second vertex
    * @returns {boolean} True if vertices are connected
    */
   areConnected( vertexA, vertexB )
   {
      return this.findEdge( vertexA, vertexB ) !== null;
   }

   /**
    * Get the degree (number of connections) of a vertex
    * @param {XXGraphVertex} vertex - Vertex to check
    * @returns {number} Degree of the vertex
    */
   getVertexDegree( vertex )
   {
      return this.getVertexEdges( vertex ).length;
   }

   /**
    * String representation of graph
    * @returns {string} String representation
    */
   toString()
   {
      return `Graph[vertices: ${this.vertexCount()}, edges: ${this.edgeCount()}]`;
   }

   /**
    * Create a copy of this graph
    * @returns {XXGraph} Copy of this graph
    */
   clone()
   {
      const newGraph = new XXGraph();

      // Clone vertices
      const vertexMap = new Map();
      for ( const vertex of this.vertexList )
      {
         const newVertex = vertex.clone();
         newGraph.addVertex( newVertex );
         vertexMap.set( vertex, newVertex );
      }

      // Clone edges with new vertex references
      for ( const edge of this.edgeList )
      {
         const newVertexA = vertexMap.get( edge.getVertexA() );
         const newVertexB = vertexMap.get( edge.getVertexB() );
         const newEdge = new XXGraphEdge( newVertexA, newVertexB, edge.getForwardWeight(), edge.getBackwardWeight() );
         newGraph.addEdge( newEdge );
      }

      return newGraph;
   }

   /**
    * Convert graph to adjacency matrix
    * @returns {number[][]} 2D array representing adjacency matrix
    */
   toAdjacencyMatrix()
   {
      const size = this.vertexCount();
      const matrix = Array( size ).fill().map( () => Array( size ).fill( 0 ) );

      for ( const edge of this.edgeList )
      {
         const indexA = this.vertexIndex( edge.getVertexA() );
         const indexB = this.vertexIndex( edge.getVertexB() );

         if ( edge.hasForwardLink() )
         {
            matrix[ indexA ][ indexB ] = edge.getForwardWeight();
         }
         if ( edge.hasBackwardLink() )
         {
            matrix[ indexB ][ indexA ] = edge.getBackwardWeight();
         }
      }

      return matrix;
   }

   /**
    * Create graph from adjacency matrix
    * @param {number[][]} matrix - 2D adjacency matrix
    * @param {string[]} [vertexNames] - Optional array of vertex names
    * @returns {XXGraph} Graph created from matrix
    */
   static fromAdjacencyMatrix( matrix, vertexNames = null )
   {
      const graph = new XXGraph();
      const size = matrix.length;

      // Create vertices
      const vertices = [];
      for ( let i = 0; i < size; i++ )
      {
         const name = vertexNames ? vertexNames[ i ] : `V${i}`;
         const vertex = new XXGraphVertex( name );
         graph.addVertex( vertex );
         vertices.push( vertex );
      }

      // Create edges
      for ( let i = 0; i < size; i++ )
      {
         for ( let j = 0; j < size; j++ )
         {
            const weight = matrix[ i ][ j ];
            if ( weight !== 0 )
            {
               // Check if edge already exists (for undirected graphs)
               const existingEdge = graph.findEdge( vertices[ i ], vertices[ j ] );

               if ( existingEdge )
               {
                  // Update backward weight
                  existingEdge.setBackwardWeight( weight );
               } else
               {
                  // Check for reverse edge
                  const reverseEdge = graph.findEdge( vertices[ j ], vertices[ i ] );
                  if ( reverseEdge )
                  {
                     // Update forward weight of reverse edge as backward
                     reverseEdge.setBackwardWeight( reverseEdge.getForwardWeight() );
                     reverseEdge.setForwardWeight( weight );
                  } else
                  {
                     // Create new edge
                     const edge = new XXGraphEdge( vertices[ i ], vertices[ j ], weight );
                     graph.addEdge( edge );
                  }
               }
            }
         }
      }

      return graph;
   }
}

export default XXGraph;