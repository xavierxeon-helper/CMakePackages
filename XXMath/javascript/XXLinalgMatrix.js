/**
 * XXLinalgMatrix - NxM matrix representation
 * JavaScript translation of XX::Linalg::Matrix class
 */

class XXLinalgMatrix
{
   /**
    * Create a matrix
    * @param {number} rowCount - Number of rows (default 0)
    * @param {number} columnCount - Number of columns (default 0)
    */
   constructor ( rowCount = 0, columnCount = 0 )
   {
      this.rowCount = rowCount;
      this.columnCount = columnCount;
      this.data = new Array( rowCount * columnCount ).fill( 0.0 );
   }

   /**
    * Cell structure for setting multiple values
    */
   static createCell( rowIndex, columnIndex, value )
   {
      return { rowIndex, columnIndex, value };
   }

   /**
    * Check equality with another matrix
    * @param {XXLinalgMatrix} other - Other matrix
    * @returns {boolean} True if matrices are equal
    */
   equals( other )
   {
      if ( !this.sizeMatch( other ) )
      {
         return false;
      }

      for ( let rowIndex = 0; rowIndex < this.rowCount; rowIndex++ )
      {
         for ( let columnIndex = 0; columnIndex < this.columnCount; columnIndex++ )
         {
            const index = this.dataIndex( rowIndex, columnIndex );
            if ( this.data[ index ] !== other.data[ index ] )
            {
               return false;
            }
         }
      }

      return true;
   }

   /**
    * Check inequality with another matrix
    * @param {XXLinalgMatrix} other - Other matrix
    * @returns {boolean} True if matrices are not equal
    */
   notEquals( other )
   {
      return !this.equals( other );
   }

   /**
    * Add matrices
    * @param {XXLinalgMatrix} other - Matrix to add
    * @returns {XXLinalgMatrix} Result matrix
    */
   add( other )
   {
      const result = this.clone();
      result.addInPlace( other );
      return result;
   }

   /**
    * Subtract matrices
    * @param {XXLinalgMatrix} other - Matrix to subtract
    * @returns {XXLinalgMatrix} Result matrix
    */
   subtract( other )
   {
      const result = this.clone();
      result.subtractInPlace( other );
      return result;
   }

   /**
    * Matrix multiplication
    * @param {XXLinalgMatrix} other - Matrix to multiply
    * @returns {XXLinalgMatrix} Result matrix
    */
   multiply( other )
   {
      if ( this.columnCount !== other.rowCount )
      {
         return new XXLinalgMatrix(); // Return empty matrix
      }

      const result = new XXLinalgMatrix( this.rowCount, other.columnCount );
      for ( let rowIndex = 0; rowIndex < this.rowCount; rowIndex++ )
      {
         for ( let columnIndex = 0; columnIndex < other.columnCount; columnIndex++ )
         {
            let value = 0.0;
            for ( let commonIndex = 0; commonIndex < this.columnCount; commonIndex++ )
            {
               value += this.getValue( rowIndex, commonIndex ) * other.getValue( commonIndex, columnIndex );
            }
            result.setValue( rowIndex, columnIndex, value );
         }
      }
      return result;
   }

   /**
    * Scalar multiplication
    * @param {number} value - Scalar value
    * @returns {XXLinalgMatrix} Result matrix
    */
   multiplyScalar( value )
   {
      const result = this.clone();
      result.multiplyScalarInPlace( value );
      return result;
   }

   /**
    * Scalar division
    * @param {number} value - Scalar value
    * @returns {XXLinalgMatrix} Result matrix
    */
   divideScalar( value )
   {
      const result = this.clone();
      result.divideScalarInPlace( value );
      return result;
   }

   /**
    * Add matrix in place
    * @param {XXLinalgMatrix} other - Matrix to add
    * @returns {XXLinalgMatrix} This matrix (for chaining)
    */
   addInPlace( other )
   {
      if ( !this.sizeMatch( other ) )
      {
         return this;
      }

      for ( let rowIndex = 0; rowIndex < this.rowCount; rowIndex++ )
      {
         for ( let columnIndex = 0; columnIndex < this.columnCount; columnIndex++ )
         {
            const index = this.dataIndex( rowIndex, columnIndex );
            this.data[ index ] += other.data[ index ];
         }
      }

      return this;
   }

   /**
    * Subtract matrix in place
    * @param {XXLinalgMatrix} other - Matrix to subtract
    * @returns {XXLinalgMatrix} This matrix (for chaining)
    */
   subtractInPlace( other )
   {
      if ( !this.sizeMatch( other ) )
      {
         return this;
      }

      for ( let rowIndex = 0; rowIndex < this.rowCount; rowIndex++ )
      {
         for ( let columnIndex = 0; columnIndex < this.columnCount; columnIndex++ )
         {
            const index = this.dataIndex( rowIndex, columnIndex );
            this.data[ index ] -= other.data[ index ];
         }
      }

      return this;
   }

   /**
    * Multiply by scalar in place
    * @param {number} value - Scalar value
    * @returns {XXLinalgMatrix} This matrix (for chaining)
    */
   multiplyScalarInPlace( value )
   {
      for ( let rowIndex = 0; rowIndex < this.rowCount; rowIndex++ )
      {
         for ( let columnIndex = 0; columnIndex < this.columnCount; columnIndex++ )
         {
            const index = this.dataIndex( rowIndex, columnIndex );
            this.data[ index ] *= value;
         }
      }

      return this;
   }

   /**
    * Divide by scalar in place
    * @param {number} value - Scalar value
    * @returns {XXLinalgMatrix} This matrix (for chaining)
    */
   divideScalarInPlace( value )
   {
      for ( let rowIndex = 0; rowIndex < this.rowCount; rowIndex++ )
      {
         for ( let columnIndex = 0; columnIndex < this.columnCount; columnIndex++ )
         {
            const index = this.dataIndex( rowIndex, columnIndex );
            this.data[ index ] /= value;
         }
      }

      return this;
   }

   /**
    * Get matrix element
    * @param {number} rowIndex - Row index
    * @param {number} columnIndex - Column index
    * @returns {number} Element value
    */
   get( rowIndex, columnIndex )
   {
      return this.getValue( rowIndex, columnIndex );
   }

   /**
    * Set matrix element
    * @param {number} rowIndex - Row index
    * @param {number} columnIndex - Column index
    * @param {number} value - Value to set
    */
   set( rowIndex, columnIndex, value )
   {
      this.setValue( rowIndex, columnIndex, value );
   }

   /**
    * Get matrix element value
    * @param {number} rowIndex - Row index
    * @param {number} columnIndex - Column index
    * @returns {number} Element value or 0.0 if out of bounds
    */
   getValue( rowIndex, columnIndex )
   {
      const index = this.dataIndex( rowIndex, columnIndex );
      if ( index >= this.data.length )
      {
         return 0.0;
      }

      return this.data[ index ];
   }

   /**
    * Set matrix element value
    * @param {number} rowIndex - Row index
    * @param {number} columnIndex - Column index
    * @param {number} value - Value to set
    */
   setValue( rowIndex, columnIndex, value )
   {
      const index = this.dataIndex( rowIndex, columnIndex );
      if ( index >= this.data.length )
      {
         return;
      }

      this.data[ index ] = value;
   }

   /**
    * Set multiple matrix values from cell list
    * @param {Array} cellList - Array of cell objects {rowIndex, columnIndex, value}
    */
   setValues( cellList )
   {
      for ( const cell of cellList )
      {
         const index = this.dataIndex( cell.rowIndex, cell.columnIndex );
         if ( index < this.data.length )
         {
            this.data[ index ] = cell.value;
         }
      }
   }

   /**
    * Check if matrices have same dimensions
    * @param {XXLinalgMatrix} other - Other matrix
    * @returns {boolean} True if sizes match
    */
   sizeMatch( other )
   {
      return this.rowCount === other.rowCount && this.columnCount === other.columnCount;
   }

   /**
    * Check if matrix is empty (null)
    * @returns {boolean} True if matrix is empty
    */
   isNull()
   {
      return this.data.length === 0;
   }

   /**
    * Get number of rows
    * @returns {number} Row count
    */
   getRowCount()
   {
      return this.rowCount;
   }

   /**
    * Get number of columns
    * @returns {number} Column count
    */
   getColumnCount()
   {
      return this.columnCount;
   }

   /**
    * Get matrix transpose
    * @returns {XXLinalgMatrix} Transposed matrix
    */
   transpose()
   {
      const result = new XXLinalgMatrix( this.columnCount, this.rowCount );
      for ( let rowIndex = 0; rowIndex < this.rowCount; rowIndex++ )
      {
         for ( let columnIndex = 0; columnIndex < this.columnCount; columnIndex++ )
         {
            const value = this.getValue( rowIndex, columnIndex );
            result.setValue( columnIndex, rowIndex, value );
         }
      }
      return result;
   }

   /**
    * Calculate matrix determinant
    * @returns {number} Determinant value
    */
   determinant()
   {
      if ( this.data.length === 0 )
      {
         return 0.0;
      }

      if ( this.rowCount !== this.columnCount )
      {
         return 0.0;
      }

      return this.subDeterminant( this );
   }

   /**
    * Calculate matrix inverse
    * @returns {XXLinalgMatrix} Inverse matrix
    */
   inverse()
   {
      const det = this.determinant();
      const c = this.cofactor();
      const ct = c.transpose();

      return ct.divideScalar( det );
   }

   /**
    * Calculate matrix cofactor
    * @returns {XXLinalgMatrix} Cofactor matrix
    */
   cofactor()
   {
      const result = new XXLinalgMatrix( this.rowCount, this.columnCount );

      for ( let rowIndex = 0; rowIndex < this.rowCount; rowIndex++ )
      {
         for ( let columnIndex = 0; columnIndex < this.columnCount; columnIndex++ )
         {
            const subMatrix = new XXLinalgMatrix( this.rowCount - 1, this.columnCount - 1 );

            let subColumnIndex = 0;
            for ( let i = 0; i < this.rowCount; i++ )
            {
               if ( i === rowIndex ) continue;

               let subRowIndex = 0;
               for ( let j = 0; j < this.columnCount; j++ )
               {
                  if ( j === columnIndex ) continue;

                  const entry = this.getValue( i, j );
                  subMatrix.setValue( subRowIndex, subColumnIndex, entry );
                  subRowIndex++;
               }
               subColumnIndex++;
            }

            const positive = ( ( rowIndex + columnIndex ) % 2 === 0 );
            const sign = positive ? 1 : -1;
            const cofactorValue = sign * subMatrix.determinant();

            result.setValue( rowIndex, columnIndex, cofactorValue );
         }
      }

      return result;
   }

   /**
    * Calculate determinant recursively (Laplace expansion)
    * @param {XXLinalgMatrix} matrix - Matrix to calculate determinant for
    * @returns {number} Determinant value
    * @private
    */
   subDeterminant( matrix )
   {
      const n = matrix.rowCount;
      if ( n === 1 )
      {
         return matrix.getValue( 0, 0 );
      }

      let value = 0.0;
      for ( let column = 0; column < n; column++ )
      {
         const subMatrix = new XXLinalgMatrix( n - 1, n - 1 );

         let columnIndex = 0;
         for ( let i = 1; i < n; i++ )
         {
            let rowIndex = 0;
            for ( let j = 0; j < n; j++ )
            {
               if ( j !== column )
               { // exclude the current column
                  const entry = matrix.getValue( i, j );
                  subMatrix.setValue( rowIndex, columnIndex, entry );
                  rowIndex++;
               }
            }
            columnIndex++;
         }

         const sign = ( column % 2 === 0 ) ? 1 : -1;
         value += sign * matrix.getValue( 0, column ) * this.subDeterminant( subMatrix );
      }

      return value;
   }

   /**
    * Calculate data index from row and column indices
    * @param {number} rowIndex - Row index
    * @param {number} columnIndex - Column index
    * @returns {number} Data array index
    * @private
    */
   dataIndex( rowIndex, columnIndex )
   {
      return ( columnIndex * this.rowCount ) + rowIndex;
   }

   /**
    * Create a copy of this matrix
    * @returns {XXLinalgMatrix} Matrix copy
    */
   clone()
   {
      const result = new XXLinalgMatrix( this.rowCount, this.columnCount );
      result.data = [ ...this.data ];
      return result;
   }

   /**
    * String representation of matrix
    * @returns {string} String representation
    */
   toString()
   {
      let result = `[${this.rowCount}rows,${this.columnCount}columns]=`;

      for ( let rowIndex = 0; rowIndex < this.rowCount; rowIndex++ )
      {
         result += "(";
         for ( let columnIndex = 0; columnIndex < this.columnCount; columnIndex++ )
         {
            if ( columnIndex !== 0 )
            {
               result += ",";
            }
            const index = this.dataIndex( rowIndex, columnIndex );
            const value = this.data[ index ];
            result += value;
         }
         result += ")";
      }
      return result;
   }

   /**
    * Create identity matrix
    * @param {number} size - Matrix size (square)
    * @returns {XXLinalgMatrix} Identity matrix
    */
   static identity( size )
   {
      const result = new XXLinalgMatrix( size, size );
      for ( let i = 0; i < size; i++ )
      {
         result.setValue( i, i, 1.0 );
      }
      return result;
   }

   /**
    * Create matrix from 2D array
    * @param {number[][]} array2D - 2D array representing matrix
    * @returns {XXLinalgMatrix} Matrix created from array
    */
   static fromArray2D( array2D )
   {
      if ( !array2D || array2D.length === 0 )
      {
         return new XXLinalgMatrix();
      }

      const rows = array2D.length;
      const cols = array2D[ 0 ].length;
      const matrix = new XXLinalgMatrix( rows, cols );

      for ( let i = 0; i < rows; i++ )
      {
         for ( let j = 0; j < cols; j++ )
         {
            matrix.setValue( i, j, array2D[ i ][ j ] || 0 );
         }
      }

      return matrix;
   }

   /**
    * Convert matrix to 2D array
    * @returns {number[][]} 2D array representation
    */
   toArray2D()
   {
      const result = [];
      for ( let i = 0; i < this.rowCount; i++ )
      {
         const row = [];
         for ( let j = 0; j < this.columnCount; j++ )
         {
            row.push( this.getValue( i, j ) );
         }
         result.push( row );
      }
      return result;
   }
}

export default XXLinalgMatrix;