/**
 * XXLinalgSpherical - Spherical coordinates representation
 * JavaScript translation of XX::Linalg::Spherical class
 */

class XXLinalgSpherical
{
   /**
    * Create a spherical coordinate
    * @param {number} az - Azimuth angle (default 0.0)
    * @param {number} el - Elevation angle (default 0.0) 
    * @param {number} radius - Radius (default 1.0)
    */
   constructor ( az = 0.0, el = 0.0, radius = 1.0 )
   {
      this.az = az;
      this.el = el;
      this.radius = radius;
   }

   /**
    * Compare spherical coordinates for ordering
    * @param {XXLinalgSpherical} other - Other spherical coordinate
    * @returns {boolean} True if this < other
    */
   isLessThan( other )
   {
      if ( this.az < other.az )
      {
         return true;
      } else if ( this.az > other.az )
      {
         return false;
      } else
      {
         return this.el < other.el;
      }
   }

   /**
    * String representation of spherical coordinates
    * @returns {string} String representation
    */
   toString()
   {
      return `spherical[${this.az}, ${this.el}, ${this.radius}]`;
   }

   /**
    * Create a copy of this spherical coordinate
    * @returns {XXLinalgSpherical} Copy of this instance
    */
   clone()
   {
      return new XXLinalgSpherical( this.az, this.el, this.radius );
   }

   /**
    * Check equality with another spherical coordinate
    * @param {XXLinalgSpherical} other - Other coordinate to compare
    * @returns {boolean} True if equal
    */
   equals( other )
   {
      return this.az === other.az &&
         this.el === other.el &&
         this.radius === other.radius;
   }
}

export default XXLinalgSpherical;