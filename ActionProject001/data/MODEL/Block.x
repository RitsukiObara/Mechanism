xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 42;
 -45.00000;100.00000;45.00000;,
 45.00000;100.00000;45.00000;,
 45.00000;100.00000;-45.00000;,
 -45.00000;100.00000;-45.00000;,
 -45.00000;95.00000;-50.00000;,
 45.00000;95.00000;-50.00000;,
 45.00000;5.00000;-50.00000;,
 -45.00000;5.00000;-50.00000;,
 -45.00000;0.00000;-45.00000;,
 45.00000;0.00000;-45.00000;,
 45.00000;0.00000;45.00000;,
 -45.00000;0.00000;45.00000;,
 -45.00000;5.00000;50.00000;,
 45.00000;5.00000;50.00000;,
 45.00000;95.00000;50.00000;,
 -45.00000;95.00000;50.00000;,
 50.00000;95.00000;45.00000;,
 50.00000;5.00000;45.00000;,
 50.00000;5.00000;-45.00000;,
 50.00000;95.00000;-45.00000;,
 -50.00000;5.00000;45.00000;,
 -50.00000;95.00000;45.00000;,
 -50.00000;95.00000;-45.00000;,
 -50.00000;5.00000;-45.00000;,
 -45.00000;100.00000;-45.00000;,
 45.00000;100.00000;-45.00000;,
 45.00000;95.00000;-50.00000;,
 -45.00000;5.00000;-50.00000;,
 45.00000;5.00000;-50.00000;,
 45.00000;0.00000;-45.00000;,
 -45.00000;95.00000;50.00000;,
 45.00000;95.00000;50.00000;,
 45.00000;100.00000;45.00000;,
 -45.00000;0.00000;45.00000;,
 45.00000;0.00000;45.00000;,
 45.00000;5.00000;50.00000;,
 50.00000;95.00000;-45.00000;,
 50.00000;5.00000;-45.00000;,
 50.00000;5.00000;45.00000;,
 -50.00000;95.00000;-45.00000;,
 -50.00000;95.00000;45.00000;,
 -50.00000;5.00000;-45.00000;;
 
 26;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,21,22,23;,
 4;24,25,26,4;,
 4;27,28,29,8;,
 4;30,31,32,0;,
 4;33,34,35,12;,
 4;25,32,16,36;,
 4;34,29,37,38;,
 4;0,24,39,40;,
 4;8,33,20,41;,
 4;28,26,36,37;,
 4;31,35,38,16;,
 4;4,27,41,39;,
 4;12,30,40,20;,
 3;25,36,26;,
 3;4,39,24;,
 3;28,37,29;,
 3;31,16,32;,
 3;8,41,27;,
 3;34,38,35;,
 3;0,40,30;,
 3;12,20,33;;
 
 MeshMaterialList {
  1;
  26;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\Block.png";
   }
  }
 }
 MeshNormals {
  24;
  -0.367001;0.854763;0.367001;,
  0.367001;0.854763;0.367001;,
  -0.367001;0.854763;-0.367001;,
  0.367001;0.854763;-0.367001;,
  -0.367001;0.367001;-0.854763;,
  0.367001;0.367001;-0.854763;,
  -0.367001;-0.367001;-0.854763;,
  0.367001;-0.367001;-0.854763;,
  -0.367001;-0.854763;-0.367001;,
  0.367001;-0.854763;-0.367001;,
  -0.367001;-0.854763;0.367001;,
  0.367001;-0.854763;0.367001;,
  -0.367001;-0.367001;0.854763;,
  0.367001;-0.367001;0.854763;,
  -0.367001;0.367001;0.854763;,
  0.367001;0.367001;0.854763;,
  0.854763;0.367001;0.367001;,
  0.854763;-0.367001;0.367001;,
  0.854763;0.367001;-0.367001;,
  0.854763;-0.367001;-0.367001;,
  -0.854763;-0.367001;0.367001;,
  -0.854763;0.367001;0.367001;,
  -0.854763;-0.367001;-0.367001;,
  -0.854763;0.367001;-0.367001;;
  26;
  4;0,1,3,2;,
  4;4,5,7,6;,
  4;8,9,11,10;,
  4;12,13,15,14;,
  4;16,17,19,18;,
  4;20,21,23,22;,
  4;2,3,5,4;,
  4;6,7,9,8;,
  4;14,15,1,0;,
  4;10,11,13,12;,
  4;3,1,16,18;,
  4;11,9,19,17;,
  4;0,2,23,21;,
  4;8,10,20,22;,
  4;7,5,18,19;,
  4;15,13,17,16;,
  4;4,6,22,23;,
  4;12,14,21,20;,
  3;3,18,5;,
  3;4,23,2;,
  3;7,19,9;,
  3;15,16,1;,
  3;8,22,6;,
  3;11,17,13;,
  3;0,21,14;,
  3;12,20,10;;
 }
 MeshTextureCoords {
  42;
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}
