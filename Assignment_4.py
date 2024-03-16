'''  ASSIGNMENT 4

Code to store a Sparse Matrix in a compressed row storage(CSR) format and
given the CSR matrix and a vector, calculate the matrix vector product.

Name = Umanshiva
Roll NO. = AI22BTECH11016
'''

# A function get_csr to form a csr matrix for a given sparse matrix as arguement.
def get_csr(matrix):
    
    #list of values to store non-zero values in a given sparse matrix
    value = []
    
    #list of column index corresponding to the index of the non-zero element in the given sparse matrix.
    col_index = []
    
    #list of row index to keep track of the index of above list which indicates from 
    # which idex the row(of the given sparse matrix) starts.
    row_index = [0]
    
    #number of rows and column of the matrix.
    n = len(matrix)
    
    for i in range(n):
        l = 0
        for j in range(n):
            if matrix[i][j] != 0:
                value.append(matrix[i][j])
                col_index.append(j)
                l += 1
        row_index.append(row_index[i] + l)
        
    row_index.pop()
    
    #returning a dictionary of the above created/updated list which indicates the matrix in CSR format.
    return {"value": value, "column_index": col_index, "row_index": row_index}


#A function to calculate the matric vector product between a matrix given in CSR format and a vector.
def matrix_vector_product(csr_matrix, vector):
    
    #The resultant vector.
    mvp = []
    
    #The size of the vector
    n = len(vector)
    
    for i in range(n):
        sum = 0
        #Condition to check whether the given row has any non-zero element.
        if i == 0 and csr_matrix['row_index'][i + 1] != 0:
            for j in range(csr_matrix['row_index'][i], csr_matrix['row_index'][i + 1]):
                k = csr_matrix['column_index'][j]
                v = csr_matrix['value'][j]
                sum += v*vector[k]
        
        #Condition to check whether the given row has any non-zero element.   
        elif 0 < i < (n - 1) and csr_matrix['row_index'][i] != csr_matrix['row_index'][i + 1]: 
            for j in range(csr_matrix['row_index'][i], csr_matrix['row_index'][i + 1]):
                k = csr_matrix['column_index'][j]
                v = csr_matrix['value'][j]
                sum += v*vector[k]
                
        elif i == (n - 1):
             for j in range(csr_matrix['row_index'][i], len(csr_matrix['column_index'])):
                k = csr_matrix['column_index'][j]
                v = csr_matrix['value'][j]
                sum += v*vector[k]
        else:
            mvp.append(sum)
            continue
                
        mvp.append(sum)             
    
    #returning the resultant vector
    return mvp
    
    
#The main function
def main():
    
    #The size of matrix and vector
    n = int(input("Enter the size of the matrix and the vector: \n"))
    print("Enter the sparse matrix(Each element is to be added line-by-line row-wise): ")
    
    #The sparse matrix(Each element is to be added line-by-line row-wise) 
    matrix = []
    for i in range(n):
        values = []
        for j in range(n):
            values.append(int(input()))
        matrix.append(values)
        
    print("Enter the vector: ")
    
    #The vector 
    vector = []
    for i in range(n):
            vector.append(int(input()))
         
    #Forming the CSR matrix for the given sparse matrix   
    csr_matrix = get_csr(matrix)
    print(csr_matrix)
    
    #calculating the matrix-vector-product
    mvp = matrix_vector_product(csr_matrix, vector)
    print(mvp)
    

#Calling the main function 
if __name__ == "__main__":
    main()