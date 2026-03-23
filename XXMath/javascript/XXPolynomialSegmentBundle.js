import XXPolynomialSegment from './XXPolynomialSegment.js';

/**
 * XXPolynomialSegmentBundle - Collection of polynomial segments
 * JavaScript translation of XX::Polynomial::Segment::Bundle class
 */

class XXPolynomialSegmentBundle extends Array
{
   /**
    * Create a new segment bundle
    */
   constructor ()
   {
      super();
   }

   /**
    * Add a segment to the bundle
    * @param {XXPolynomialSegment} segment - Segment to add
    * @returns {number} New length of bundle
    */
   addSegment( segment )
   {
      return this.push( segment );
   }

   /**
    * Remove a segment from the bundle
    * @param {XXPolynomialSegment} segment - Segment to remove
    * @returns {boolean} True if segment was removed
    */
   removeSegment( segment )
   {
      const index = this.indexOf( segment );
      if ( index !== -1 )
      {
         this.splice( index, 1 );
         return true;
      }
      return false;
   }

   /**
    * Get segment at index
    * @param {number} index - Index of segment
    * @returns {XXPolynomialSegment|undefined} Segment at index
    */
   getSegment( index )
   {
      return this[ index ];
   }

   /**
    * Get number of segments
    * @returns {number} Number of segments
    */
   getSegmentCount()
   {
      return this.length;
   }

   /**
    * Clear all segments
    */
   clear()
   {
      this.length = 0;
   }

   /**
    * Find segment containing the given x value
    * @param {number} x - X value to search for
    * @returns {XXPolynomialSegment|null} Segment containing x, or null if not found
    */
   findSegmentContaining( x )
   {
      for ( const segment of this )
      {
         if ( segment.containsX( x ) )
         {
            return segment;
         }
      }
      return null;
   }

   /**
    * Evaluate the bundle at given x value
    * @param {number} x - X value
    * @returns {number|null} Value at x, or null if x is outside all segments
    */
   evaluate( x )
   {
      const segment = this.findSegmentContaining( x );
      return segment ? segment.value( x ) : null;
   }

   /**
    * Get the overall start of the bundle (minimum start of all segments)
    * @returns {number|null} Overall start, or null if bundle is empty
    */
   getOverallStart()
   {
      if ( this.length === 0 ) return null;
      return Math.min( ...this.map( seg => seg.getStart() ) );
   }

   /**
    * Get the overall end of the bundle (maximum end of all segments)
    * @returns {number|null} Overall end, or null if bundle is empty
    */
   getOverallEnd()
   {
      if ( this.length === 0 ) return null;
      return Math.max( ...this.map( seg => seg.getEnd() ) );
   }

   /**
    * Get the overall length of the bundle
    * @returns {number|null} Overall length, or null if bundle is empty
    */
   getOverallLength()
   {
      const start = this.getOverallStart();
      const end = this.getOverallEnd();
      return ( start !== null && end !== null ) ? end - start : null;
   }

   /**
    * Sort segments by start position
    * @returns {XXPolynomialSegmentBundle} This bundle (for chaining)
    */
   sortByStart()
   {
      this.sort( ( a, b ) => a.getStart() - b.getStart() );
      return this;
   }

   /**
    * Check if segments overlap
    * @returns {boolean} True if any segments overlap
    */
   hasOverlaps()
   {
      for ( let i = 0; i < this.length; i++ )
      {
         for ( let j = i + 1; j < this.length; j++ )
         {
            const seg1 = this[ i ];
            const seg2 = this[ j ];
            if ( this.segmentsOverlap( seg1, seg2 ) )
            {
               return true;
            }
         }
      }
      return false;
   }

   /**
    * Check if two segments overlap
    * @param {XXPolynomialSegment} seg1 - First segment
    * @param {XXPolynomialSegment} seg2 - Second segment
    * @returns {boolean} True if segments overlap
    * @private
    */
   segmentsOverlap( seg1, seg2 )
   {
      return !( seg1.getEnd() <= seg2.getStart() || seg2.getEnd() <= seg1.getStart() );
   }

   /**
    * Get gaps between segments (assumes segments are sorted)
    * @returns {Array} Array of gap objects {start, end, length}
    */
   getGaps()
   {
      if ( this.length < 2 ) return [];

      const sortedSegments = [ ...this ].sort( ( a, b ) => a.getStart() - b.getStart() );
      const gaps = [];

      for ( let i = 0; i < sortedSegments.length - 1; i++ )
      {
         const currentEnd = sortedSegments[ i ].getEnd();
         const nextStart = sortedSegments[ i + 1 ].getStart();

         if ( nextStart > currentEnd )
         {
            gaps.push( {
               start: currentEnd,
               end: nextStart,
               length: nextStart - currentEnd
            } );
         }
      }

      return gaps;
   }

   /**
    * Merge overlapping segments (simple algorithm)
    * @returns {XXPolynomialSegmentBundle} New bundle with merged segments
    */
   mergeOverlapping()
   {
      if ( this.length <= 1 ) return this.clone();

      const sorted = [ ...this ].sort( ( a, b ) => a.getStart() - b.getStart() );
      const merged = new XXPolynomialSegmentBundle();

      let current = sorted[ 0 ].clone();

      for ( let i = 1; i < sorted.length; i++ )
      {
         const next = sorted[ i ];

         if ( current.getEnd() >= next.getStart() )
         {
            // Overlapping - extend current segment
            current.setEnd( Math.max( current.getEnd(), next.getEnd() ) );
         } else
         {
            // No overlap - add current and start new
            merged.push( current );
            current = next.clone();
         }
      }

      merged.push( current );
      return merged;
   }

   /**
    * Sample all segments at given resolution
    * @param {number} pointsPerUnit - Points per unit length
    * @returns {Object} Object with x and y arrays
    */
   sample( pointsPerUnit = 10 )
   {
      const x = [];
      const y = [];

      for ( const segment of this )
      {
         const numPoints = Math.max( 2, Math.ceil( segment.getLength() * pointsPerUnit ) );
         const { x: segX, y: segY } = segment.sample( numPoints );
         x.push( ...segX );
         y.push( ...segY );
      }

      return { x, y };
   }

   /**
    * Translate all segments by offset
    * @param {number} offset - Amount to translate
    * @returns {XXPolynomialSegmentBundle} New translated bundle
    */
   translate( offset )
   {
      const translated = new XXPolynomialSegmentBundle();
      for ( const segment of this )
      {
         translated.push( segment.translate( offset ) );
      }
      return translated;
   }

   /**
    * Create a copy of this bundle
    * @returns {XXPolynomialSegmentBundle} Copy of this bundle
    */
   clone()
   {
      const copy = new XXPolynomialSegmentBundle();
      for ( const segment of this )
      {
         copy.push( segment.clone() );
      }
      return copy;
   }

   /**
    * String representation of bundle
    * @returns {string} String representation
    */
   toString()
   {
      return `SegmentBundle[${this.length} segments, range: ${this.getOverallStart()} to ${this.getOverallEnd()}]`;
   }

   /**
    * Convert to JSON array
    * @returns {Array} JSON representation
    */
   toJSON()
   {
      return this.map( segment => segment.save() );
   }

   /**
    * Load from JSON array
    * @param {Array} data - JSON array of segment data
    * @returns {XXPolynomialSegmentBundle} Bundle loaded from JSON
    */
   static fromJSON( data )
   {
      const bundle = new XXPolynomialSegmentBundle();
      for ( const segmentData of data )
      {
         const segment = new XXPolynomialSegment();
         segment.load( segmentData );
         bundle.push( segment );
      }
      return bundle;
   }

   /**
    * Create bundle from array of segments
    * @param {XXPolynomialSegment[]} segments - Array of segments
    * @returns {XXPolynomialSegmentBundle} New bundle
    */
   static fromSegments( segments )
   {
      const bundle = new XXPolynomialSegmentBundle();
      for ( const segment of segments )
      {
         bundle.push( segment );
      }
      return bundle;
   }
}

export default XXPolynomialSegmentBundle;