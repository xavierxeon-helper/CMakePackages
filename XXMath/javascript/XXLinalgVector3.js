import XXMath from './XXMath.js';
import XXLinalgSpherical from './XXLinalgSpherical.js';

/**
 * XXLinalgVector3 - 3D vector representation
 * JavaScript translation of XX::Linalg::Vector3 class
 * Used to represent points or directions in 3D space
 */

class XXLinalgVector3
{
   static X = 0;
   static Y = 1;
   static Z = 2;

   /**
    * Create a 3D vector
    * @param {number} x - X component (default 0.0)
    * @param {number} y - Y component (default 0.0)
    * @param {number} z - Z component (default 0.0)
    */
   constructor ( x = 0.0, y = 0.0, z = 0.0 )
   {
      this.x = x;
      this.y = y;
      this.z = z;
      this.data = [ x, y, z ]; // Array access for compatibility
   }

   /**
    * Check equality with another vector
    * @param {XXLinalgVector3} other - Other vector
    * @returns {boolean} True if vectors are equal
    */
   equals( other )
   {
      return this.x === other.x && this.y === other.y && this.z === other.z;
   }

   /**
    * Compare vectors for ordering
    * @param {XXLinalgVector3} other - Other vector
    * @returns {boolean} True if this < other
    */
   isLessThan( other )
   {
      if ( this.x < other.x )
      {
         return true;
      } else if ( this.x > other.x )
      {
         return false;
      } else if ( this.y < other.y )
      {
         return true;
      } else if ( this.y > other.y )
      {
         return false;
      } else
      {
         return this.z < other.z;
      }
   }

   /**
    * Add two vectors
    * @param {XXLinalgVector3} other - Vector to add
    * @returns {XXLinalgVector3} Result vector
    */
   add( other )
   {
      return new XXLinalgVector3(
         this.x + other.x,
         this.y + other.y,
         this.z + other.z
      );
   }

   /**
    * Add another vector to this vector (in-place)
    * @param {XXLinalgVector3} other - Vector to add
    * @returns {XXLinalgVector3} This vector (for chaining)
    */
   addInPlace( other )
   {
      this.x += other.x;
      this.y += other.y;
      this.z += other.z;
      this.data[ 0 ] = this.x;
      this.data[ 1 ] = this.y;
      this.data[ 2 ] = this.z;
      return this;
   }

   /**
    * Subtract another vector from this vector
    * @param {XXLinalgVector3} other - Vector to subtract
    * @returns {XXLinalgVector3} Result vector
    */
   subtract( other )
   {
      return new XXLinalgVector3(
         this.x - other.x,
         this.y - other.y,
         this.z - other.z
      );
   }

   /**
    * Access vector component by index
    * @param {number} index - Index (0=x, 1=y, 2=z)
    * @returns {number} Component value
    */
   get( index )
   {
      return this.data[ index ];
   }

   /**
    * Set vector component by index
    * @param {number} index - Index (0=x, 1=y, 2=z) 
    * @param {number} value - New value
    */
   set( index, value )
   {
      this.data[ index ] = value;
      if ( index === 0 ) this.x = value;
      else if ( index === 1 ) this.y = value;
      else if ( index === 2 ) this.z = value;
   }

   /**
    * Get X component
    * @returns {number} X component
    */
   getX()
   {
      return this.x;
   }

   /**
    * Get Y component
    * @returns {number} Y component
    */
   getY()
   {
      return this.y;
   }

   /**
    * Get Z component
    * @returns {number} Z component
    */
   getZ()
   {
      return this.z;
   }

   /**
    * Create vector from spherical coordinates
    * @param {XXLinalgSpherical} spherical - Spherical coordinates
    * @param {boolean} fromDegree - True if angles are in degrees (default true)
    * @returns {XXLinalgVector3} Vector in Cartesian coordinates
    */
   static fromSpherical( spherical, fromDegree = true )
   {
      let az = spherical.az;
      let el = spherical.el;

      if ( fromDegree )
      {
         az = XXMath.deg2Rad( az );
         el = XXMath.deg2Rad( el );
      }

      const x = spherical.radius * Math.sin( el ) * Math.cos( az );
      const y = spherical.radius * Math.sin( el ) * Math.sin( az );
      const z = spherical.radius * Math.cos( el );

      return new XXLinalgVector3( x, y, z );
   }

   /**
    * Convert vector to spherical coordinates
    * @param {boolean} toDegree - True to convert angles to degrees (default true)
    * @returns {XXLinalgSpherical} Spherical coordinates
    */
   toSpherical( toDegree = true )
   {
      const radius = this.length();
      if ( radius === 0.0 )
      {
         return new XXLinalgSpherical();
      }

      let el = Math.acos( this.z / radius );

      const planeRadius = Math.sqrt( ( this.x * this.x ) + ( this.y * this.y ) );
      let az = ( planeRadius > 0 ) ? Math.acos( this.x / planeRadius ) : 0.0;
      if ( this.y < 0 )
      {
         az = ( 2 * XXMath.pi ) - az;
      }

      if ( toDegree )
      {
         az = XXMath.rad2Deg( az );
         el = XXMath.rad2Deg( el );
      }

      return new XXLinalgSpherical( az, el, radius );
   }

   /**
    * Calculate vector length (magnitude)
    * @returns {number} Vector length
    */
   length()
   {
      const selfDot = this.dot( this );
      return Math.sqrt( selfDot );
   }

   /**
    * Get normalized vector (unit vector)
    * @returns {XXLinalgVector3} Normalized vector
    */
   normalize()
   {
      const l = this.length();
      if ( l === 0.0 )
      {
         return new XXLinalgVector3( 0.0, 0.0, 0.0 );
      }

      return new XXLinalgVector3(
         this.x / l,
         this.y / l,
         this.z / l
      );
   }

   /**
    * Calculate dot product with another vector
    * @param {XXLinalgVector3} other - Other vector
    * @returns {number} Dot product
    */
   dot( other )
   {
      return ( this.x * other.x ) + ( this.y * other.y ) + ( this.z * other.z );
   }

   /**
    * Calculate angle between vectors using dot product
    * @param {XXLinalgVector3} other - Other vector
    * @param {boolean} toDegree - True to return angle in degrees (default true)
    * @returns {number} Angle between vectors
    */
   dotAngle( other, toDegree = true )
   {
      const d = this.dot( other );
      const l = this.length() * other.length();
      let angle = Math.acos( d / l );

      if ( toDegree )
      {
         angle = XXMath.rad2Deg( angle );
      }

      return angle;
   }

   /**
    * Calculate cross product with another vector
    * @param {XXLinalgVector3} other - Other vector
    * @returns {XXLinalgVector3} Cross product vector
    */
   cross( other )
   {
      const x = ( this.y * other.z ) - ( this.z * other.y );
      const y = ( this.z * other.x ) - ( this.x * other.z );
      const z = ( this.x * other.y ) - ( this.y * other.x );

      return new XXLinalgVector3( x, y, z );
   }

   /**
    * Calculate angle between vectors using cross product
    * @param {XXLinalgVector3} other - Other vector
    * @param {boolean} toDegree - True to return angle in degrees (default true)
    * @returns {number} Angle between vectors
    */
   crossAngle( other, toDegree = true )
   {
      const c = this.cross( other ).length();
      const l = this.length() * other.length();
      let angle = Math.asin( c / l );

      if ( toDegree )
      {
         angle = XXMath.rad2Deg( angle );
      }

      return angle;
   }

   /**
    * Scale vector by a scalar
    * @param {number} scalar - Scaling factor
    * @returns {XXLinalgVector3} Scaled vector
    */
   scale( scalar )
   {
      return new XXLinalgVector3(
         this.x * scalar,
         this.y * scalar,
         this.z * scalar
      );
   }

   /**
    * Create a copy of this vector
    * @returns {XXLinalgVector3} Copy of this vector
    */
   clone()
   {
      return new XXLinalgVector3( this.x, this.y, this.z );
   }

   /**
    * String representation of vector
    * @returns {string} String representation
    */
   toString()
   {
      return `[${this.x}, ${this.y}, ${this.z}]`;
   }

   /**
    * Convert to array
    * @returns {number[]} Array representation [x, y, z]
    */
   toArray()
   {
      return [ this.x, this.y, this.z ];
   }

   /**
    * Create vector from array
    * @param {number[]} array - Array with at least 3 elements
    * @returns {XXLinalgVector3} Vector created from array
    */
   static fromArray( array )
   {
      return new XXLinalgVector3( array[ 0 ] || 0, array[ 1 ] || 0, array[ 2 ] || 0 );
   }
}

export default XXLinalgVector3;