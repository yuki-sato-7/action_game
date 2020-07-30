xof 0303txt 0032
template ColorRGBA {
 <35ff44e0-6c7c-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <d3e16e81-7835-11cf-8f52-0040333594a3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template Material {
 <3d82ab4d-62da-11cf-ab39-0020af71e433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template TextureFilename {
 <a42790e1-7810-11cf-8f52-0040333594a3>
 STRING filename;
}

template Frame {
 <3d82ab46-62da-11cf-ab39-0020af71e433>
 [...]
}

template Matrix4x4 {
 <f6f23f45-7686-11cf-8f52-0040333594a3>
 array FLOAT matrix[16];
}

template FrameTransformMatrix {
 <f6f23f41-7686-11cf-8f52-0040333594a3>
 Matrix4x4 frameMatrix;
}

template Vector {
 <3d82ab5e-62da-11cf-ab39-0020af71e433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template MeshFace {
 <3d82ab5f-62da-11cf-ab39-0020af71e433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template Mesh {
 <3d82ab44-62da-11cf-ab39-0020af71e433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

template MeshNormals {
 <f6f23f43-7686-11cf-8f52-0040333594a3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshMaterialList {
 <f6f23f42-7686-11cf-8f52-0040333594a3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material <3d82ab4d-62da-11cf-ab39-0020af71e433>]
}

template Coords2d {
 <f6f23f44-7686-11cf-8f52-0040333594a3>
 FLOAT u;
 FLOAT v;
}

template MeshTextureCoords {
 <f6f23f40-7686-11cf-8f52-0040333594a3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}


Material Mat_lambert6 {
 1.000000;1.000000;1.000000;1.000000;;
 0.000000;
 0.000000;0.000000;0.000000;;
 0.000000;0.000000;0.000000;;

 TextureFilename {
  "lambert1_Base_Color.png";
 }
}

Frame SceneRoot {
 

 FrameTransformMatrix {
  1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 Frame Coliseum_model_2_fbx {
  

  FrameTransformMatrix {
   1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
  }

  Frame lambert6 {
   

   FrameTransformMatrix {
    1.000000,0.000000,0.000000,0.000000,0.000000,-0.000000,-1.000000,0.000000,0.000000,1.000000,-0.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
   }

   Mesh lambert6 {
    16;
    -1699.99974;1699.99974;0.000000;,
    0.000000;0.000000;0.000000;,
    0.000000;1699.99974;0.000000;,
    -1699.99974;0.000000;0.000000;,
    0.000000;1699.99974;0.000000;,
    1699.99974;0.000000;0.000000;,
    1699.99974;1699.99974;0.000000;,
    0.000000;0.000000;0.000000;,
    -1699.99974;0.000000;0.000000;,
    0.000000;-1699.99974;0.000000;,
    0.000000;0.000000;0.000000;,
    -1699.99974;-1699.99974;0.000000;,
    0.000000;0.000000;0.000000;,
    1699.99974;-1699.99974;0.000000;,
    1699.99974;0.000000;0.000000;,
    0.000000;-1699.99974;0.000000;;
    8;
    3;0,1,2;,
    3;1,0,3;,
    3;4,5,6;,
    3;5,4,7;,
    3;8,9,10;,
    3;9,8,11;,
    3;12,13,14;,
    3;13,12,15;;

    MeshNormals {
     16;
     0.000000;0.000000;1.000000;,
     0.000000;0.000000;1.000000;,
     0.000000;0.000000;1.000000;,
     0.000000;0.000000;1.000000;,
     0.000000;0.000000;1.000000;,
     0.000000;0.000000;1.000000;,
     0.000000;0.000000;1.000000;,
     0.000000;0.000000;1.000000;,
     0.000000;0.000000;1.000000;,
     0.000000;0.000000;1.000000;,
     0.000000;0.000000;1.000000;,
     0.000000;0.000000;1.000000;,
     0.000000;0.000000;1.000000;,
     0.000000;0.000000;1.000000;,
     0.000000;0.000000;1.000000;,
     0.000000;0.000000;1.000000;;
     8;
     3;0,1,2;,
     3;1,0,3;,
     3;4,5,6;,
     3;5,4,7;,
     3;8,9,10;,
     3;9,8,11;,
     3;12,13,14;,
     3;13,12,15;;
    }

    MeshMaterialList {
     1;
     8;
     0,
     0,
     0,
     0,
     0,
     0,
     0,
     0;
     { Mat_lambert6 }
    }

    MeshTextureCoords c1 {
     16;
     0.017298;0.988782;,
     0.985715;0.020503;,
     0.985646;0.988851;,
     0.017367;0.020434;,
     0.985695;0.020483;,
     0.017317;0.988802;,
     0.017347;0.020454;,
     0.985666;0.988831;,
     0.985619;0.020407;,
     0.017394;0.988878;,
     0.017271;0.020530;,
     0.985742;0.988755;,
     0.017332;0.988816;,
     0.985680;0.020469;,
     0.985680;0.988816;,
     0.017332;0.020469;;
    }
   }
  }
 }
}