import XXMath from './XXMath.js';

/**
 * XXLinalgQuaternion - Quaternion representation for 3D rotations
 * JavaScript translation of XX::Linalg::Quaternion class
 * Extended with standard quaternion operations
 */

class XXLinalgQuaternion
{
   /**
    * Create a quaternion
    * @param {number} w - W component (scalar part, default 1.0)
    * @param {number} x - X component (vector part, default 0.0)
    * @param {number} y - Y component (vector part, default 0.0)
    * @param {number} z - Z component (vector part, default 0.0)
    */
   constructor ( w = 1.0, x = 0.0, y = 0.0, z = 0.0 )
   {
      this.w = w;
      this.x = x;
      this.y = y;
      this.z = z;
   }

   /**
    * Check equality with another quaternion
    * @param {XXLinalgQuaternion} other - Other quaternion
    * @returns {boolean} True if quaternions are equal
    */
   equals( other )
   {
      return this.w === other.w &&
         this.x === other.x &&
         this.y === other.y &&
         this.z === other.z;
   }

   /**
    * Add two quaternions
    * @param {XXLinalgQuaternion} other - Quaternion to add
    * @returns {XXLinalgQuaternion} Result quaternion
    */
   add( other )
   {
      return new XXLinalgQuaternion(
         this.w + other.w,
         this.x + other.x,
         this.y + other.y,
         this.z + other.z
      );
   }

   /**
    * Subtract quaternion
    * @param {XXLinalgQuaternion} other - Quaternion to subtract
    * @returns {XXLinalgQuaternion} Result quaternion
    */
   subtract( other )
   {
      return new XXLinalgQuaternion(
         this.w - other.w,
         this.x - other.x,
         this.y - other.y,
         this.z - other.z
      );
   }

   /**
    * Multiply quaternions (Hamilton product)
    * @param {XXLinalgQuaternion} other - Quaternion to multiply
    * @returns {XXLinalgQuaternion} Result quaternion
    */
   multiply( other )
   {
      const w = this.w * other.w - this.x * other.x - this.y * other.y - this.z * other.z;
      const x = this.w * other.x + this.x * other.w + this.y * other.z - this.z * other.y;
      const y = this.w * other.y - this.x * other.z + this.y * other.w + this.z * other.x;
      const z = this.w * other.z + this.x * other.y - this.y * other.x + this.z * other.w;

      return new XXLinalgQuaternion( w, x, y, z );
   }

   /**
    * Scale quaternion by scalar
    * @param {number} scalar - Scaling factor
    * @returns {XXLinalgQuaternion} Scaled quaternion
    */
   scale( scalar )
   {
      return new XXLinalgQuaternion(
         this.w * scalar,
         this.x * scalar,
         this.y * scalar,
         this.z * scalar
      );
   }

   /**
    * Calculate quaternion magnitude (norm)
    * @returns {number} Quaternion magnitude
    */
   magnitude()
   {
      return Math.sqrt( this.w * this.w + this.x * this.x + this.y * this.y + this.z * this.z );
   }

   /**
    * Get normalized quaternion (unit quaternion)
    * @returns {XXLinalgQuaternion} Normalized quaternion
    */
   normalize()
   {
      const mag = this.magnitude();
      if ( mag === 0.0 )
      {
         return new XXLinalgQuaternion( 1.0, 0.0, 0.0, 0.0 );
      }
      return this.scale( 1.0 / mag );
   }

   /**
    * Get quaternion conjugate
    * @returns {XXLinalgQuaternion} Conjugate quaternion
    */
   conjugate()
   {
      return new XXLinalgQuaternion( this.w, -this.x, -this.y, -this.z );
   }

   /**
    * Get quaternion inverse
    * @returns {XXLinalgQuaternion} Inverse quaternion
    */
   inverse()
   {
      const magSq = this.w * this.w + this.x * this.x + this.y * this.y + this.z * this.z;
      if ( magSq === 0.0 )
      {
         return new XXLinalgQuaternion(); // Return identity
      }
      const conjugate = this.conjugate();
      return conjugate.scale( 1.0 / magSq );
   }

   /**
    * Calculate dot product with another quaternion
    * @param {XXLinalgQuaternion} other - Other quaternion
    * @returns {number} Dot product
    */
   dot( other )
   {
      return this.w * other.w + this.x * other.x + this.y * other.y + this.z * other.z;
   }

   /**
    * Create quaternion from axis-angle representation
    * @param {import('./XXLinalgVector3.js').default} axis - Rotation axis (normalized)
    * @param {number} angle - Rotation angle in radians
    * @returns {XXLinalgQuaternion} Quaternion representing the rotation
    */
   static fromAxisAngle( axis, angle )
   {
      const halfAngle = angle * 0.5;
      const sinHalf = Math.sin( halfAngle );
      const cosHalf = Math.cos( halfAngle );

      return new XXLinalgQuaternion(
         cosHalf,
         axis.x * sinHalf,
         axis.y * sinHalf,
         axis.z * sinHalf
      );
   }

   /**
    * Create quaternion from Euler angles (ZYX order)
    * @param {number} yaw - Yaw angle (Z-axis rotation) in radians
    * @param {number} pitch - Pitch angle (Y-axis rotation) in radians
    * @param {number} roll - Roll angle (X-axis rotation) in radians
    * @returns {XXLinalgQuaternion} Quaternion representing the rotation
    */
   static fromEuler( yaw, pitch, roll )
   {
      const cy = Math.cos( yaw * 0.5 );
      const sy = Math.sin( yaw * 0.5 );
      const cp = Math.cos( pitch * 0.5 );
      const sp = Math.sin( pitch * 0.5 );
      const cr = Math.cos( roll * 0.5 );
      const sr = Math.sin( roll * 0.5 );

      const w = cr * cp * cy + sr * sp * sy;
      const x = sr * cp * cy - cr * sp * sy;
      const y = cr * sp * cy + sr * cp * sy;
      const z = cr * cp * sy - sr * sp * cy;

      return new XXLinalgQuaternion( w, x, y, z );
   }

   /**
    * Convert quaternion to Euler angles (ZYX order)
    * @param {boolean} toDegree - True to return angles in degrees (default true)
    * @returns {Object} Object with yaw, pitch, roll properties
    */
   toEuler( toDegree = true )
   {
      // Roll (x-axis rotation)
      const sinr_cosp = 2 * ( this.w * this.x + this.y * this.z );
      const cosr_cosp = 1 - 2 * ( this.x * this.x + this.y * this.y );
      let roll = Math.atan2( sinr_cosp, cosr_cosp );

      // Pitch (y-axis rotation)
      const sinp = 2 * ( this.w * this.y - this.z * this.x );
      let pitch;
      if ( Math.abs( sinp ) >= 1 )
      {
         pitch = Math.sign( sinp ) * Math.PI / 2; // Use 90 degrees if out of range
      } else
      {
         pitch = Math.asin( sinp );
      }

      // Yaw (z-axis rotation)
      const siny_cosp = 2 * ( this.w * this.z + this.x * this.y );
      const cosy_cosp = 1 - 2 * ( this.y * this.y + this.z * this.z );
      let yaw = Math.atan2( siny_cosp, cosy_cosp );

      if ( toDegree )
      {
         roll = XXMath.rad2Deg( roll );
         pitch = XXMath.rad2Deg( pitch );
         yaw = XXMath.rad2Deg( yaw );
      }

      return { yaw, pitch, roll };
   }

   /**
    * Spherical linear interpolation between two quaternions
    * @param {XXLinalgQuaternion} other - Target quaternion
    * @param {number} t - Interpolation parameter (0 to 1)
    * @returns {XXLinalgQuaternion} Interpolated quaternion
    */
   slerp( other, t )
   {
      let dot = this.dot( other );

      // If dot product is negative, slerp won't take the shorter path
      let q2 = other;
      if ( dot < 0.0 )
      {
         q2 = other.scale( -1 );
         dot = -dot;
      }

      if ( dot > 0.9995 )
      {
         // If the quaternions are very close, use linear interpolation
         const result = this.add( q2.subtract( this ).scale( t ) );
         return result.normalize();
      }

      const theta_0 = Math.acos( Math.abs( dot ) );
      const sin_theta_0 = Math.sin( theta_0 );
      const theta = theta_0 * t;
      const sin_theta = Math.sin( theta );

      const s0 = Math.cos( theta ) - dot * sin_theta / sin_theta_0;
      const s1 = sin_theta / sin_theta_0;

      return this.scale( s0 ).add( q2.scale( s1 ) );
   }

   /**
    * Create a copy of this quaternion
    * @returns {XXLinalgQuaternion} Copy of this quaternion
    */
   clone()
   {
      return new XXLinalgQuaternion( this.w, this.x, this.y, this.z );
   }

   /**
    * String representation of quaternion
    * @returns {string} String representation
    */
   toString()
   {
      return `quaternion[${this.w}, ${this.x}, ${this.y}, ${this.z}]`;
   }

   /**
    * Convert to array
    * @returns {number[]} Array representation [w, x, y, z]
    */
   toArray()
   {
      return [ this.w, this.x, this.y, this.z ];
   }

   /**
    * Create quaternion from array
    * @param {number[]} array - Array with at least 4 elements [w, x, y, z]
    * @returns {XXLinalgQuaternion} Quaternion created from array
    */
   static fromArray( array )
   {
      return new XXLinalgQuaternion(
         array[ 0 ] || 1.0,
         array[ 1 ] || 0.0,
         array[ 2 ] || 0.0,
         array[ 3 ] || 0.0
      );
   }

   /**
    * Identity quaternion (no rotation)
    * @returns {XXLinalgQuaternion} Identity quaternion
    */
   static identity()
   {
      return new XXLinalgQuaternion( 1.0, 0.0, 0.0, 0.0 );
   }
}

export default XXLinalgQuaternion;