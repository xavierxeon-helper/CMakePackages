import XXPolynomialSegmentBundle from './XXPolynomialSegmentBundle.js';
import XXPolynomialSegment from './XXPolynomialSegment.js';
import XXLinalgMatrix from './XXLinalgMatrix.js';

/**
 * XXPolynomialRegression - Fit polynomials to data
 * JavaScript translation of XX::Polynomial::Regression class
 * See https://en.wikipedia.org/wiki/Polynomial_regression
 */

class XXPolynomialRegression
{
   /**
    * Section structure for regression analysis
    */
   static Section = class
   {
      constructor ( start = 0, end = 0, steady = false )
      {
         this.start = start;
         this.end = end;
         this.steady = steady; // no jump to next section
      }

      /**
       * Get section length
       * @returns {number} Section length
       */
      length()
      {
         return this.end - this.start;
      }
   };

   /**
    * Create a polynomial regression analyzer
    * @param {number} size - Size of data array
    */
   constructor ( size )
   {
      this.values = new Array( size ).fill( 0.0 );
   }

   /**
    * Get size of data array
    * @returns {number} Size of data array
    */
   size()
   {
      return this.values.length;
   }

   /**
    * Set value at index
    * @param {number} index - Index to set
    * @param {number} value - Value to set
    */
   setValue( index, value )
   {
      if ( index >= 0 && index < this.values.length )
      {
         this.values[ index ] = value;
      }
   }

   /**
    * Get value at index
    * @param {number} index - Index to get
    * @returns {number} Value at index or 0 if invalid index
    */
   getValue( index )
   {
      return ( index >= 0 && index < this.values.length ) ? this.values[ index ] : 0.0;
   }

   /**
    * Set all values from array
    * @param {number[]} values - Array of values
    */
   setValues( values )
   {
      const minLength = Math.min( this.values.length, values.length );
      for ( let i = 0; i < minLength; i++ )
      {
         this.values[ i ] = values[ i ];
      }
   }

   /**
    * Clear all values (set to zero)
    */
   clear()
   {
      this.values.fill( 0.0 );
   }

   /**
    * Get copy of values array
    * @returns {number[]} Copy of values array
    */
   getValues()
   {
      return [ ...this.values ];
   }

   /**
    * Fit polynomial segments to data
    * @param {number} degree - Polynomial degree
    * @param {number} threshold - Threshold for section detection
    * @param {number} overFit - Amount of overfitting to allow (default 2)
    * @param {number} maxSegmentLength - Maximum segment length (default 50)
    * @returns {XXPolynomialSegmentBundle} Bundle of fitted polynomial segments
    */
   fit( degree, threshold, overFit = 2, maxSegmentLength = 50 )
   {
      const sections = this.compileSections( threshold, maxSegmentLength );
      const bundle = new XXPolynomialSegmentBundle();

      for ( let sectionIndex = 0; sectionIndex < sections.length; sectionIndex++ )
      {
         const section = sections[ sectionIndex ];
         const segment = this.fitSection( section, degree, sections, sectionIndex, overFit );
         bundle.push( segment );
      }

      return bundle;
   }

   /**
    * Fit a polynomial to a specific section
    * @param {XXPolynomialRegression.Section} section - Section to fit
    * @param {number} degree - Polynomial degree
    * @param {XXPolynomialRegression.Section[]} allSections - All sections 
    * @param {number} sectionIndex - Index of current section
    * @param {number} overFit - Overfitting parameter
    * @returns {XXPolynomialSegment} Fitted polynomial segment
    * @private
    */
   fitSection( section, degree, allSections, sectionIndex, overFit )
   {
      const segment = new XXPolynomialSegment( degree );
      segment.setStart( section.start );
      segment.setEnd( section.end );

      let length = section.length();
      let start = section.start;

      // Extend backwards if steady sections exist
      const extendBackwards = ( offset ) =>
      {
         if ( overFit === offset ) return;

         const compareIndex = sectionIndex - offset;
         if ( compareIndex <= 0 ) return;

         const prevSection = allSections[ compareIndex - 1 ];
         if ( prevSection.steady )
         {
            length += prevSection.length();
            start = prevSection.start;
            extendBackwards( offset + 1 );
         }
      };

      extendBackwards( 1 );

      // Extend forwards if steady sections exist
      const extendForwards = ( offset ) =>
      {
         if ( overFit === offset ) return;

         const compareIndex = sectionIndex + offset;
         if ( compareIndex + 1 >= allSections.length ) return;

         const compareSection = allSections[ compareIndex ];
         if ( !compareSection.steady ) return;

         const nextSection = allSections[ compareIndex + 1 ];
         length += nextSection.length();
         extendForwards( offset + 1 );
      };

      extendForwards( 1 );

      // Perform polynomial regression using least squares
      const coefficients = this.performRemathematicsRegression( start, length, degree );
      for ( let i = 0; i < coefficients.length && i <= degree; i++ )
      {
         segment.setCoefficient( i, coefficients[ i ] || 0 );
      }

      return segment;
   }

   /**
    * Perform polynomial regression using least squares method
    * @param {number} start - Start index for regression
    * @param {number} length - Number of data points
    * @param {number} degree - Polynomial degree
    * @returns {number[]} Polynomial coefficients
    * @private
    */
   performRemathematicsRegression( start, length, degree )
   {
      if ( length <= degree )
      {
         // Not enough points for regression, return zeros
         return new Array( degree + 1 ).fill( 0 );
      }

      // Build Vandermonde matrix and target vector
      const A = [];
      const b = [];

      for ( let i = 0; i < length; i++ )
      {
         const x = i;
         const y = this.values[ start + i ] || 0;

         const row = [];
         for ( let j = degree; j >= 0; j-- )
         {
            row.push( Math.pow( x, j ) );
         }
         A.push( row );
         b.push( y );
      }

      // Solve using normal equations: (A^T * A) * x = A^T * b
      return this.solveNormalEquations( A, b );
   }

   /**
    * Solve normal equations for least squares
    * @param {number[][]} A - Design matrix
    * @param {number[]} b - Target vector
    * @returns {number[]} Solution coefficients
    * @private
    */
   solveNormalEquations( A, b )
   {
      const m = A.length; // number of observations
      const n = A[ 0 ].length; // number of coefficients

      // Compute A^T * A
      const AtA = Array( n ).fill().map( () => Array( n ).fill( 0 ) );
      for ( let i = 0; i < n; i++ )
      {
         for ( let j = 0; j < n; j++ )
         {
            for ( let k = 0; k < m; k++ )
            {
               AtA[ i ][ j ] += A[ k ][ i ] * A[ k ][ j ];
            }
         }
      }

      // Compute A^T * b
      const Atb = Array( n ).fill( 0 );
      for ( let i = 0; i < n; i++ )
      {
         for ( let k = 0; k < m; k++ )
         {
            Atb[ i ] += A[ k ][ i ] * b[ k ];
         }
      }

      // Solve AtA * x = Atb using Gaussian elimination
      return this.solveLinearSystem( AtA, Atb );
   }

   /**
    * Solve linear system using Gaussian elimination
    * @param {number[][]} A - Coefficient matrix
    * @param {number[]} b - Right hand side
    * @returns {number[]} Solution vector
    * @private
    */
   solveLinearSystem( A, b )
   {
      const n = A.length;
      const augmented = A.map( ( row, i ) => [ ...row, b[ i ] ] );

      // Forward elimination
      for ( let i = 0; i < n; i++ )
      {
         // Find pivot
         let maxRow = i;
         for ( let k = i + 1; k < n; k++ )
         {
            if ( Math.abs( augmented[ k ][ i ] ) > Math.abs( augmented[ maxRow ][ i ] ) )
            {
               maxRow = k;
            }
         }
         [ augmented[ i ], augmented[ maxRow ] ] = [ augmented[ maxRow ], augmented[ i ] ];

         // Make all rows below this one 0 in current column
         for ( let k = i + 1; k < n; k++ )
         {
            const factor = augmented[ k ][ i ] / augmented[ i ][ i ];
            for ( let j = i; j < n + 1; j++ )
            {
               if ( i === j )
               {
                  augmented[ k ][ j ] = 0;
               } else
               {
                  augmented[ k ][ j ] -= factor * augmented[ i ][ j ];
               }
            }
         }
      }

      // Back substitution
      const x = new Array( n );
      for ( let i = n - 1; i >= 0; i-- )
      {
         x[ i ] = augmented[ i ][ n ];
         for ( let j = i + 1; j < n; j++ )
         {
            x[ i ] -= augmented[ i ][ j ] * x[ j ];
         }
         x[ i ] /= augmented[ i ][ i ];
      }

      return x;
   }

   /**
    * Compile sections based on threshold analysis
    * @param {number} threshold - Threshold for determining steady sections
    * @param {number} maxSegmentLength - Maximum segment length
    * @returns {XXPolynomialRegression.Section[]} Array of sections
    */
   compileSections( threshold, maxSegmentLength = 50 )
   {
      const sections = [];

      if ( this.values.length === 0 )
      {
         return sections;
      }

      let currentStart = 0;
      let i = 0;

      while ( i < this.values.length )
      {
         let segmentLength = 0;
         let lastValue = this.values[ i ];
         let steady = true;

         // Find end of current section
         while ( i < this.values.length && segmentLength < maxSegmentLength )
         {
            const currentValue = this.values[ i ];
            const difference = Math.abs( currentValue - lastValue );

            if ( difference > threshold )
            {
               steady = false;
            }

            lastValue = currentValue;
            i++;
            segmentLength++;

            // If we hit threshold or max length, end section
            if ( !steady && difference > threshold * 2 )
            {
               break;
            }
         }

         const section = new XXPolynomialRegression.Section( currentStart, i - 1, steady );
         sections.push( section );
         currentStart = i - 1;
      }

      // Ensure we don't have empty sections
      return sections.filter( section => section.length() > 0 );
   }

   /**
    * Calculate basic statistics for the data
    * @returns {Object} Statistics object {mean, variance, stdDev, min, max}
    */
   calculateStatistics()
   {
      if ( this.values.length === 0 )
      {
         return { mean: 0, variance: 0, stdDev: 0, min: 0, max: 0 };
      }

      const sum = this.values.reduce( ( a, b ) => a + b, 0 );
      const mean = sum / this.values.length;
      const variance = this.values.reduce( ( a, b ) => a + Math.pow( b - mean, 2 ), 0 ) / this.values.length;
      const stdDev = Math.sqrt( variance );
      const min = Math.min( ...this.values );
      const max = Math.max( ...this.values );

      return { mean, variance, stdDev, min, max };
   }

   /**
    * Create regression from array data
    * @param {number[]} data - Input data array
    * @returns {XXPolynomialRegression} New regression instance
    */
   static fromArray( data )
   {
      const regression = new XXPolynomialRegression( data.length );
      regression.setValues( data );
      return regression;
   }

   /**
    * String representation of regression
    * @returns {string} String representation
    */
   toString()
   {
      const stats = this.calculateStatistics();
      return `PolynomialRegression[${this.size()} points, mean: ${stats.mean.toFixed( 3 )}, range: ${stats.min.toFixed( 3 )} to ${stats.max.toFixed( 3 )}]`;
   }
}

export default XXPolynomialRegression;