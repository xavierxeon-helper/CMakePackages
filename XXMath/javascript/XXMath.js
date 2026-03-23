/**
 * XXMath - Basic mathematical utilities
 * JavaScript translation of XX::Math namespace
 */

class XXMath
{
   static pi = 2.0 * Math.asin( 1.0 );
   static epsilon = 1e-12;

   /**
    * Convert degrees to radians
    * @param {number} degrees - Angle in degrees
    * @returns {number} Angle in radians
    */
   static deg2Rad( degrees )
   {
      return degrees * ( this.pi / 180 );
   }

   /**
    * Convert radians to degrees
    * @param {number} radians - Angle in radians
    * @returns {number} Angle in degrees
    */
   static rad2Deg( radians )
   {
      return radians * ( 180 / this.pi );
   }

   /**
    * Check if there is a sign change between two values
    * @param {number} value1 - First value
    * @param {number} value2 - Second value
    * @returns {boolean} True if there is a sign change
    */
   static signChange( value1, value2 )
   {
      if ( value1 < 0.0 && value2 >= 0.0 )
      {
         return true;
      } else if ( value1 >= 0.0 && value2 < 0.0 )
      {
         return true;
      } else
      {
         return false;
      }
   }

   /**
    * Get the nearest power of two that is greater than or equal to the given number
    * @param {number} num - Input number
    * @returns {number} Nearest power of two
    */
   static getNearestPowerOfTwo( num )
   {
      if ( num === 0 )
      {
         return 1;
      }

      let powerOfTwo = 1;
      while ( powerOfTwo < num )
      {
         powerOfTwo <<= 1;
      }

      return powerOfTwo;
   }

   /**
    * Check if a number is a power of two
    * @param {number} num - Number to check
    * @returns {boolean} True if the number is a power of two
    */
   static isPowerOfTwo( num )
   {
      return num === this.getNearestPowerOfTwo( num );
   }

   /**
    * Calculate numerical derivative of values array
    * @param {number[]} values - Array of values
    * @param {number} order - Order of derivative (default 1)
    * @returns {number[]} Derivative values
    */
   static derivative( values, order = 1 )
   {
      if ( order === 0 )
      {
         return values.slice(); // return copy
      }

      const derivedValues = new Array( values.length ).fill( 0.0 );
      for ( let index = 1; index < values.length; index++ )
      {
         const y1 = values[ index - 1 ];
         const y2 = values[ index ];
         const diff = y2 - y1;
         derivedValues[ index ] = diff;
      }

      return this.derivative( derivedValues, order - 1 );
   }
}

export default XXMath;