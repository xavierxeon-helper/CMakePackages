/**
 * XXMath Library - JavaScript Translation
 * Complete translation of the C++ XXMath library to JavaScript
 */

// Basic Math utilities
import XXMath from './XXMath.js';

// Linear Algebra classes
import XXLinalgSpherical from './XXLinalgSpherical.js';
import XXLinalgVector3 from './XXLinalgVector3.js';
import XXLinalgMatrix from './XXLinalgMatrix.js';
import XXLinalgQuaternion from './XXLinalgQuaternion.js';

// Graph classes
import XXGraph from './XXGraph.js';
import XXGraphVertex from './XXGraphVertex.js';
import XXGraphEdge from './XXGraphEdge.js';

// Polynomial classes
import XXPolynomial from './XXPolynomial.js';
import XXPolynomialSegment from './XXPolynomialSegment.js';
import XXPolynomialSegmentBundle from './XXPolynomialSegmentBundle.js';
import XXPolynomialRegression from './XXPolynomialRegression.js';

// Export all classes
export
{
   // Math utilities
   XXMath,

   // Linear algebra
   XXLinalgSpherical,
   XXLinalgVector3,
   XXLinalgMatrix,
   XXLinalgQuaternion,

   // Graph structures
   XXGraph,
   XXGraphVertex,
   XXGraphEdge,

   // Polynomials
   XXPolynomial,
   XXPolynomialSegment,
   XXPolynomialSegmentBundle,
   XXPolynomialRegression
};

// Default export with namespace-like structure for compatibility
export default {
   Math: XXMath,

   Linalg: {
      Spherical: XXLinalgSpherical,
      Vector3: XXLinalgVector3,
      Matrix: XXLinalgMatrix,
      Quaternion: XXLinalgQuaternion
   },

   Graph: {
      Graph: XXGraph,
      Vertex: XXGraphVertex,
      Edge: XXGraphEdge
   },

   Polynomial: {
      Polynomial: XXPolynomial,
      Segment: XXPolynomialSegment,
      SegmentBundle: XXPolynomialSegmentBundle,
      Regression: XXPolynomialRegression
   }
};