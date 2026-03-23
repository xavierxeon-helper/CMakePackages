import XXPolynomial from './XXPolynomial.js';

/**
 * XXPolynomialSegment - Polynomial segment with start/end boundaries
 * JavaScript translation of XX::Polynomial::Segment class
 */

class XXPolynomialSegment extends XXPolynomial
{
   /**
    * Create a polynomial segment
    * @param {number|number[]} degreeOrCoefficients - Degree or coefficients array
    */
   constructor ( degreeOrCoefficients = 0 )
   {
      super( degreeOrCoefficients );
      this.start = 0.0;
      this.end = 0.0;
   }

   /**
    * Get segment start position
    * @returns {number} Start position
    */
   getStart()
   {
      return this.start;
   }

   /**
    * Get segment end position
    * @returns {number} End position
    */
   getEnd()
   {
      return this.end;
   }

   /**
    * Get segment length
    * @returns {number} Length (end - start)
    */
   getLength()
   {
      return this.end - this.start;
   }

   /**
    * Set segment start position
    * @param {number} value - Start position
    */
   setStart( value )
   {
      this.start = value;
   }

   /**
    * Set segment end position
    * @param {number} value - End position
    */
   setEnd( value )
   {
      this.end = value;
   }

   /**
    * Set both start and end positions
    * @param {number} start - Start position
    * @param {number} end - End position
    */
   setBounds( start, end )
   {
      this.start = start;
      this.end = end;
   }

   /**
    * Check if x value is within segment bounds
    * @param {number} x - X value to check
    * @returns {boolean} True if x is within bounds
    */
   containsX( x )
   {
      return x >= this.start && x <= this.end;
   }

   /**
    * Evaluate polynomial segment at given x value
    * Translates x relative to segment start
    * @param {number} x - Input value
    * @returns {number} Polynomial value at translated x
    * @override
    */
   value( x )
   {
      return super.value( x - this.start );
   }

   /**
    * Load segment from JSON object
    * @param {Object} data - JSON data
    * @override
    */
   load( data )
   {
      super.load( data );
      if ( typeof data.start === 'number' )
      {
         this.start = data.start;
      }
      if ( typeof data.end === 'number' )
      {
         this.end = data.end;
      }
   }

   /**
    * Save segment to JSON object
    * @returns {Object} JSON representation
    * @override
    */
   save()
   {
      const base = super.save();
      base.start = this.start;
      base.end = this.end;
      return base;
   }

   /**
    * Create a copy of this segment
    * @returns {XXPolynomialSegment} Copy of this segment
    */
   clone()
   {
      const copy = new XXPolynomialSegment( this.coefficients );
      copy.start = this.start;
      copy.end = this.end;
      return copy;
   }

   /**
    * String representation of segment
    * @returns {string} String representation
    * @override
    */
   toString()
   {
      const polyStr = super.toString();
      return `Segment[${this.start}, ${this.end}] with ${polyStr}`;
   }

   /**
    * Check equality with another segment
    * @param {XXPolynomialSegment} other - Other segment
    * @returns {boolean} True if segments are equal
    */
   equals( other )
   {
      return super.equals( other ) &&
         this.start === other.start &&
         this.end === other.end;
   }

   /**
    * Translate segment by offset
    * @param {number} offset - Amount to translate
    * @returns {XXPolynomialSegment} New translated segment
    */
   translate( offset )
   {
      const translated = this.clone();
      translated.start += offset;
      translated.end += offset;
      return translated;
   }

   /**
    * Scale segment bounds by factor
    * @param {number} factor - Scaling factor
    * @returns {XXPolynomialSegment} New scaled segment
    */
   scaleBounds( factor )
   {
      const scaled = this.clone();
      const center = ( this.start + this.end ) / 2;
      const halfLength = this.getLength() / 2;
      scaled.start = center - halfLength * factor;
      scaled.end = center + halfLength * factor;
      return scaled;
   }

   /**
    * Get the center point of the segment
    * @returns {number} Center point
    */
   getCenter()
   {
      return ( this.start + this.end ) / 2;
   }

   /**
    * Evaluate segment at multiple x values within bounds
    * @param {number} numPoints - Number of points to evaluate
    * @returns {Object} Object with x and y arrays
    */
   sample( numPoints = 100 )
   {
      const x = [];
      const y = [];
      const step = this.getLength() / ( numPoints - 1 );

      for ( let i = 0; i < numPoints; i++ )
      {
         const xi = this.start + i * step;
         x.push( xi );
         y.push( this.value( xi ) );
      }

      return { x, y };
   }

   /**
    * Create segment from polynomial and bounds
    * @param {XXPolynomial} polynomial - Source polynomial
    * @param {number} start - Start position
    * @param {number} end - End position
    * @returns {XXPolynomialSegment} New segment
    */
   static fromPolynomial( polynomial, start, end )
   {
      const segment = new XXPolynomialSegment( polynomial.getCoefficients() );
      segment.start = start;
      segment.end = end;
      return segment;
   }

   /**
    * Create linear segment
    * @param {number} start - Start position
    * @param {number} end - End position
    * @param {number} startValue - Value at start
    * @param {number} endValue - Value at end
    * @returns {XXPolynomialSegment} Linear segment
    */
   static linear( start, end, startValue, endValue )
   {
      const length = end - start;
      const slope = ( endValue - startValue ) / length;
      const segment = new XXPolynomialSegment( [ slope, startValue ] );
      segment.start = start;
      segment.end = end;
      return segment;
   }

   /**
    * Create constant segment
    * @param {number} start - Start position
    * @param {number} end - End position
    * @param {number} value - Constant value
    * @returns {XXPolynomialSegment} Constant segment
    */
   static constant( start, end, value )
   {
      const segment = new XXPolynomialSegment( [ value ] );
      segment.start = start;
      segment.end = end;
      return segment;
   }
}

export default XXPolynomialSegment;