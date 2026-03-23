/**
 * XXPolynomial - nth degree polynomial representation
 * JavaScript translation of XX::Polynomial class
 * Coefficients are in descending order: a(n), a(n-1), ..., a1, a0
 * See https://en.wikipedia.org/wiki/Polynomial
 */

class XXPolynomial
{
   /**
    * Create a polynomial
    * @param {number|number[]} degreeOrCoefficients - Degree of polynomial or array of coefficients
    */
   constructor ( degreeOrCoefficients = 0 )
   {
      if ( typeof degreeOrCoefficients === 'number' )
      {
         // Create polynomial with specified degree, all coefficients zero
         this.coefficients = new Array( degreeOrCoefficients + 1 ).fill( 0.0 );
      } else if ( Array.isArray( degreeOrCoefficients ) )
      {
         // Create polynomial from coefficient array
         this.coefficients = [ ...degreeOrCoefficients ];
      } else
      {
         this.coefficients = [ 0.0 ];
      }
   }

   /**
    * Copy constructor
    * @param {XXPolynomial} other - Polynomial to copy
    * @returns {XXPolynomial} New polynomial copy
    */
   static copy( other )
   {
      return new XXPolynomial( other.coefficients );
   }

   /**
    * Assign from another polynomial
    * @param {XXPolynomial} other - Polynomial to copy from
    * @returns {XXPolynomial} This polynomial (for chaining)
    */
   assign( other )
   {
      this.coefficients = [ ...other.coefficients ];
      return this;
   }

   /**
    * Evaluate polynomial at given x value
    * @param {number} x - Input value
    * @returns {number} Polynomial value at x
    */
   evaluate( x )
   {
      return this.value( x );
   }

   /**
    * Function call operator - evaluate polynomial
    * @param {number} x - Input value  
    * @returns {number} Polynomial value at x
    */
   call( x )
   {
      return this.value( x );
   }

   /**
    * Check equality with another polynomial
    * @param {XXPolynomial} other - Other polynomial
    * @returns {boolean} True if polynomials are equal
    */
   equals( other )
   {
      if ( this.coefficients.length !== other.coefficients.length )
      {
         return false;
      }

      for ( let i = 0; i < this.coefficients.length; i++ )
      {
         if ( this.coefficients[ i ] !== other.coefficients[ i ] )
         {
            return false;
         }
      }

      return true;
   }

   /**
    * Check inequality with another polynomial
    * @param {XXPolynomial} other - Other polynomial
    * @returns {boolean} True if polynomials are not equal
    */
   notEquals( other )
   {
      return !this.equals( other );
   }

   /**
    * Add two polynomials
    * @param {XXPolynomial} other - Polynomial to add
    * @returns {XXPolynomial} Result polynomial
    */
   add( other )
   {
      const maxSize = Math.max( this.coefficients.length, other.coefficients.length );
      const result = new XXPolynomial( maxSize - 1 );

      for ( let index = 0; index < maxSize; index++ )
      {
         const myValue = ( index < this.coefficients.length ) ? this.coefficients[ index ] : 0.0;
         const otherValue = ( index < other.coefficients.length ) ? other.coefficients[ index ] : 0.0;
         result.setCoefficient( index, myValue + otherValue );
      }

      return result;
   }

   /**
    * Subtract polynomials
    * @param {XXPolynomial} other - Polynomial to subtract
    * @returns {XXPolynomial} Result polynomial
    */
   subtract( other )
   {
      const maxSize = Math.max( this.coefficients.length, other.coefficients.length );
      const result = new XXPolynomial( maxSize - 1 );

      for ( let index = 0; index < maxSize; index++ )
      {
         const myValue = ( index < this.coefficients.length ) ? this.coefficients[ index ] : 0.0;
         const otherValue = ( index < other.coefficients.length ) ? other.coefficients[ index ] : 0.0;
         result.setCoefficient( index, myValue - otherValue );
      }

      return result;
   }

   /**
    * Add polynomial in place
    * @param {XXPolynomial} other - Polynomial to add
    * @returns {XXPolynomial} This polynomial (for chaining)
    */
   addInPlace( other )
   {
      // Extend coefficients array if necessary
      if ( other.coefficients.length > this.coefficients.length )
      {
         const oldLength = this.coefficients.length;
         this.coefficients.length = other.coefficients.length;
         for ( let i = oldLength; i < this.coefficients.length; i++ )
         {
            this.coefficients[ i ] = 0.0;
         }
      }

      for ( let index = 0; index < this.coefficients.length; index++ )
      {
         const otherValue = ( index < other.coefficients.length ) ? other.coefficients[ index ] : 0.0;
         this.coefficients[ index ] += otherValue;
      }

      return this;
   }

   /**
    * Subtract polynomial in place
    * @param {XXPolynomial} other - Polynomial to subtract
    * @returns {XXPolynomial} This polynomial (for chaining)
    */
   subtractInPlace( other )
   {
      // Extend coefficients array if necessary 
      if ( other.coefficients.length > this.coefficients.length )
      {
         const oldLength = this.coefficients.length;
         this.coefficients.length = other.coefficients.length;
         for ( let i = oldLength; i < this.coefficients.length; i++ )
         {
            this.coefficients[ i ] = 0.0;
         }
      }

      for ( let index = 0; index < this.coefficients.length; index++ )
      {
         const otherValue = ( index < other.coefficients.length ) ? other.coefficients[ index ] : 0.0;
         this.coefficients[ index ] -= otherValue;
      }

      return this;
   }

   /**
    * Multiply polynomial by scalar
    * @param {number} scalar - Scalar value
    * @returns {XXPolynomial} Scaled polynomial
    */
   scale( scalar )
   {
      const result = this.clone();
      for ( let i = 0; i < result.coefficients.length; i++ )
      {
         result.coefficients[ i ] *= scalar;
      }
      return result;
   }

   /**
    * Evaluate polynomial at given x value
    * @param {number} x - Input value
    * @returns {number} Polynomial value at x
    */
   value( x )
   {
      let result = 0.0;

      for ( let d = 0; d < this.coefficients.length; d++ )
      {
         const expo = this.coefficients.length - ( d + 1 );
         result += this.coefficients[ d ] * Math.pow( x, expo );
      }

      return result;
   }

   /**
    * Load polynomial from JSON object
    * @param {Object} data - JSON data containing polynomial
    */
   load( data )
   {
      if ( data.coefficients && Array.isArray( data.coefficients ) )
      {
         this.coefficients = [ ...data.coefficients ];
      }
   }

   /**
    * Save polynomial to JSON object
    * @returns {Object} JSON representation of polynomial
    */
   save()
   {
      return {
         coefficients: [ ...this.coefficients ]
      };
   }

   /**
    * Set polynomial degree (resize coefficient array)
    * @param {number} degree - New degree
    */
   setDegree( degree )
   {
      this.coefficients = new Array( degree + 1 ).fill( 0.0 );
   }

   /**
    * Get polynomial degree
    * @returns {number} Degree of polynomial
    */
   getDegree()
   {
      return Math.max( 0, this.coefficients.length - 1 );
   }

   /**
    * Get coefficients array
    * @returns {number[]} Array of coefficients
    */
   getCoefficients()
   {
      return [ ...this.coefficients ]; // Return copy
   }

   /**
    * Set coefficient at specified index
    * @param {number} index - Index of coefficient
    * @param {number} value - Coefficient value
    */
   setCoefficient( index, value )
   {
      if ( index >= 0 && index < this.coefficients.length )
      {
         this.coefficients[ index ] = value;
      }
   }

   /**
    * Get coefficient at specified index
    * @param {number} index - Index of coefficient
    * @returns {number} Coefficient value or 0 if index invalid
    */
   getCoefficient( index )
   {
      if ( index >= 0 && index < this.coefficients.length )
      {
         return this.coefficients[ index ];
      }
      return 0.0;
   }

   /**
    * Calculate derivative of polynomial
    * @returns {XXPolynomial} Derivative polynomial
    */
   derivative()
   {
      if ( this.coefficients.length <= 1 )
      {
         return new XXPolynomial( [ 0 ] ); // Derivative of constant is 0
      }

      const derivativeCoeffs = [];
      for ( let i = 0; i < this.coefficients.length - 1; i++ )
      {
         const power = this.coefficients.length - i - 1;
         derivativeCoeffs.push( this.coefficients[ i ] * power );
      }

      return new XXPolynomial( derivativeCoeffs );
   }

   /**
    * Calculate integral of polynomial (without constant of integration)
    * @returns {XXPolynomial} Integral polynomial
    */
   integral()
   {
      const integralCoeffs = [ 0 ]; // Constant of integration = 0

      for ( let i = 0; i < this.coefficients.length; i++ )
      {
         const power = this.coefficients.length - i - 1;
         integralCoeffs.splice( 0, 0, this.coefficients[ i ] / ( power + 1 ) );
      }

      return new XXPolynomial( integralCoeffs );
   }

   /**
    * Find roots of polynomial (simple implementation for quadratic)
    * @returns {number[]|null} Array of real roots, or null if not quadratic
    */
   findRoots()
   {
      if ( this.coefficients.length === 3 )
      {
         // Quadratic formula: ax² + bx + c = 0
         const a = this.coefficients[ 0 ];
         const b = this.coefficients[ 1 ];
         const c = this.coefficients[ 2 ];

         if ( a === 0 ) return null; // Not quadratic

         const discriminant = b * b - 4 * a * c;
         if ( discriminant < 0 ) return []; // No real roots

         const sqrtDisc = Math.sqrt( discriminant );
         const root1 = ( -b + sqrtDisc ) / ( 2 * a );
         const root2 = ( -b - sqrtDisc ) / ( 2 * a );

         return discriminant === 0 ? [ root1 ] : [ root1, root2 ];
      }
      return null; // Only implementing quadratic for now
   }

   /**
    * Create a copy of this polynomial
    * @returns {XXPolynomial} Copy of this polynomial
    */
   clone()
   {
      return new XXPolynomial( this.coefficients );
   }

   /**
    * String representation of polynomial
    * @returns {string} String representation
    */
   toString()
   {
      if ( this.coefficients.length === 0 )
      {
         return "Polynomial: y = 0";
      }

      let result = "Polynomial: y = ";
      let first = true;

      for ( let index = 0; index < this.coefficients.length; index++ )
      {
         const coeff = this.coefficients[ index ];
         if ( coeff === 0 ) continue;

         const power = this.coefficients.length - index - 1;

         if ( !first && coeff > 0 )
         {
            result += " + ";
         } else if ( coeff < 0 )
         {
            result += first ? "-" : " - ";
         }

         const absCoeff = Math.abs( coeff );
         if ( absCoeff !== 1 || power === 0 )
         {
            result += absCoeff;
         }

         if ( power > 0 )
         {
            if ( absCoeff !== 1 ) result += "*";
            result += "x";
            if ( power > 1 )
            {
               result += "^" + power;
            }
         }

         first = false;
      }

      return first ? "Polynomial: y = 0" : result;
   }

   /**
    * Create polynomial from roots
    * @param {number[]} roots - Array of roots
    * @returns {XXPolynomial} Polynomial with given roots
    */
   static fromRoots( roots )
   {
      let poly = new XXPolynomial( [ 1 ] ); // Start with 1

      for ( const root of roots )
      {
         // Multiply by (x - root)
         const factor = new XXPolynomial( [ 1, -root ] );
         poly = poly.multiply( factor );
      }

      return poly;
   }

   /**
    * Multiply polynomials
    * @param {XXPolynomial} other - Polynomial to multiply
    * @returns {XXPolynomial} Product polynomial
    */
   multiply( other )
   {
      if ( this.coefficients.length === 0 || other.coefficients.length === 0 )
      {
         return new XXPolynomial( [ 0 ] );
      }

      const resultDegree = this.getDegree() + other.getDegree();
      const result = new XXPolynomial( resultDegree );

      for ( let i = 0; i < this.coefficients.length; i++ )
      {
         for ( let j = 0; j < other.coefficients.length; j++ )
         {
            const power1 = this.coefficients.length - i - 1;
            const power2 = other.coefficients.length - j - 1;
            const resultPower = power1 + power2;
            const resultIndex = result.coefficients.length - resultPower - 1;

            result.coefficients[ resultIndex ] += this.coefficients[ i ] * other.coefficients[ j ];
         }
      }

      return result;
   }

   /**
    * Create zero polynomial
    * @returns {XXPolynomial} Zero polynomial
    */
   static zero()
   {
      return new XXPolynomial( [ 0 ] );
   }

   /**
    * Create constant polynomial
    * @param {number} constant - Constant value
    * @returns {XXPolynomial} Constant polynomial
    */
   static constant( constant )
   {
      return new XXPolynomial( [ constant ] );
   }

   /**
    * Create linear polynomial (ax + b)
    * @param {number} a - Coefficient of x
    * @param {number} b - Constant term
    * @returns {XXPolynomial} Linear polynomial
    */
   static linear( a, b = 0 )
   {
      return new XXPolynomial( [ a, b ] );
   }

   /**
    * Create quadratic polynomial (ax² + bx + c)
    * @param {number} a - Coefficient of x²
    * @param {number} b - Coefficient of x
    * @param {number} c - Constant term
    * @returns {XXPolynomial} Quadratic polynomial
    */
   static quadratic( a, b = 0, c = 0 )
   {
      return new XXPolynomial( [ a, b, c ] );
   }
}

export default XXPolynomial;