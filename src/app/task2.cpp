#include<iostream>
#include<math.h>
using namespace std;

class Vector3D{
public:
float x,y,z;
Vector3D();
Vector3D (float,float,float);
~Vector3D();
float dotProduct(Vector3D& v){
    return (x*v.x + y*v.y * z*v.z);

}
Vector3D cross(Vector3D& v){
    return Vector3D(
            y * v.z - z * v.y,
            z * v.x - x * v.z,
            x * v.y - y * v.x
        );};
 float norm() {
        return sqrt(x*x + y*y + z*z);
    };
    void normalize() {
        float length = norm();
        if (length > 0) {
            x /= length;
            y /= length;
            z /= length;
        }
    }
    Vector3D operator+(const Vector3D& v) { return Vector3D(x + v.x, y + v.y, z + v.z); }
    Vector3D operator-(const Vector3D& v)  { return Vector3D(x - v.x, y - v.y, z - v.z); }
    Vector3D operator*(float scalar)  { return Vector3D(x * scalar, y * scalar, z * scalar); }
    Vector3D operator/(float scalar)  { return Vector3D(x / scalar, y / scalar, z / scalar); }
    bool operator==(const Vector3D& v)  { return x == v.x && y == v.y && z == v.z; }





};
Vector3D::Vector3D () {
 x=1.0;
 y=1.0;
 z=1.0;
}
Vector3D::Vector3D (float a,float b,float c) {
 x=a;
 y=b;
 z=c;
}


class Vector4D{
public:
float x,y,z,p;
Vector4D();
Vector4D (float,float,float,float);
~Vector4D();
float dotProduct(Vector4D& v){
    return (x*v.x + y*v.y * z*v.z+p*v.p);

}

 float norm() {
        return sqrt(x*x + y*y + z*z+p*p);
    };
    void normalize() {
        float length = norm();
        if (length > 0) {
            x /= length;
            y /= length;
            z /= length;
            p /= length;
        }
    }
    Vector4D operator+(const Vector4D& v) { return Vector4D(x + v.x, y + v.y, z + v.z,p+v.p); }
    Vector4D operator-(const Vector4D& v)  { return Vector4D(x - v.x, y - v.y, z - v.z,p-v.p); }
    Vector4D operator*(float scalar)  { return Vector4D(x * scalar, y * scalar, z * scalar,p*scalar); }
    Vector4D operator/(float scalar)  { return Vector4D(x / scalar, y / scalar, z / scalar,z/scalar); }
    bool operator==(const Vector4D& v)  { return x == v.x && y == v.y && z == v.z && p==v.p ; }





};
Vector4D::Vector4D () {
 x=1.0;
 y=1.0;
 z=1.0;
 p=1.0;
}
Vector4D::Vector4D (float a,float b,float c,float d) {
 x=a;
 y=b;
 z=c;
 p=d;
}
class matrix{
    public:
    float** mat; 
    int n;



    matrix(int size,float a[]){
       int  n=size;
       mat = new float*[n];
        for (size_t i = 0; i < n; i++)
        {
            for (size_t j = 0; j < n; j++)
            {
                if(i!=j){
                    mat[i][j]=0;
                }
                else
                {
                    mat[i][i]=a[i];
                }
                
            }
            
            
        }
        

    }


};

class matrix3x3 {


    public:
    float mat [3][3];

    matrix3x3(){
        for (size_t i = 0; i < 3; i++)
        {
            for (size_t j = 0; j < 3;j++)
            {
                mat[i][j]=0;
                
            }
            
        }}
        matrix3x3 (float a[9]){
            for (size_t i = 0; i < 3; i++)
            {
                for (size_t j = 0; j < 3; j++)
                {
                    mat[i][j]=a[3*i+j];
                }
                
            }
        }
         

          matrix3x3 transpose(){
           float a[9];
           for (size_t i = 0; i < 3; i++)
           {
            for (size_t j = 0; j < 3; j++)
            {
                a[3*i+j]=mat[j][i];

               
            }
            
          
           }
         
            return matrix3x3(a);


          }

          void print() {
        for (size_t i = 0; i < 3; i++) {
            for (size_t j = 0; j < 3; j++) {
                cout << mat[i][j] << " ";
            }
            cout << endl;
        }
  };


float det(){
    float temp[3][3];  
    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            temp[i][j] = mat[i][j]; 
        }
    }

    float factor;
    float det = 1.0;

    for (size_t i = 0; i < 3; i++) {
        int pivot = i;
        float pivotValue = temp[i][i];

     
        for (size_t j = i+1; j < 3; j++) {
            if (fabs(temp[j][i]) > fabs(pivotValue)) {
                pivotValue = temp[j][i];
                pivot = j;
            }
        }

       
        if (pivot != i) {
            for (size_t col = 0; col < 3; col++) {
                swap(temp[i][col], temp[pivot][col]);
            }
            det = -det;  
        }

        
        if (temp[i][i] == 0) {
            cout << "Matrix is singular. Determinant is 0.\n";
            return 0;
        }

        
        for (size_t k = i+1; k < 3; k++) {
            factor = temp[k][i] / temp[i][i];
            for (size_t col = 0; col < 3; col++) {
                temp[k][col] -= factor * temp[i][col];
            }
        }

      
        det *= temp[i][i];

       
       
            cout << endl;
        }
        
    return det;
}

};



int main() {
    int det;
    float values[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9}; 
    matrix3x3 mat(values);

    std::cout << "Original Matrix:" << std::endl;
    mat.print();
    det= mat.det();
    std::cout<<det;
   


    matrix3x3 transposedMat = mat.transpose();

    std::cout << "\nTransposed Matrix:" << std::endl;
    transposedMat.print();

    return 0;
}
