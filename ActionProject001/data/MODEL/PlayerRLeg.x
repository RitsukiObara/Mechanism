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
 52;
 0.00016;-0.00004;0.03248;,
 1.25290;-0.00004;-1.27778;,
 0.00016;-0.00004;-1.82050;,
 0.00016;-0.00004;0.03248;,
 1.77180;-0.00004;0.03248;,
 0.00016;-0.00004;0.03248;,
 1.25290;-0.00004;1.34273;,
 0.00016;-0.00004;0.03248;,
 0.00016;-0.00004;1.88546;,
 0.00016;-0.00004;0.03248;,
 -1.25258;-0.00004;1.34273;,
 0.00016;-0.00004;0.03248;,
 -1.77149;-0.00004;0.03248;,
 0.00016;-0.00004;0.03248;,
 -1.25258;-0.00004;-1.27778;,
 0.00016;-0.00004;0.03248;,
 0.00016;-0.00004;-1.82050;,
 0.00016;-14.38557;0.03248;,
 0.00016;-14.38557;-2.22963;,
 1.52949;-14.38557;-1.56707;,
 0.00016;-14.38557;0.03248;,
 2.16297;-14.38557;0.03248;,
 0.00016;-14.38557;0.03248;,
 1.52949;-14.38557;1.63203;,
 0.00016;-14.38557;0.03248;,
 0.00016;-14.38557;2.29458;,
 0.00016;-14.38557;0.03248;,
 -1.52918;-14.38557;1.63203;,
 0.00016;-14.38557;0.03248;,
 -2.16265;-14.38557;0.03248;,
 0.00016;-14.38557;0.03248;,
 -1.52918;-14.38557;-1.56707;,
 0.00016;-14.38557;0.03248;,
 0.00016;-14.38557;-2.22963;,
 -2.02194;-1.31884;-2.08246;,
 0.00016;-1.31884;-2.95849;,
 -2.85953;-1.31884;0.03248;,
 0.00016;-1.31884;-2.95849;,
 2.02226;-1.31884;-2.08246;,
 -2.02194;-1.31884;2.14741;,
 2.85984;-1.31884;0.03248;,
 0.00016;-1.31884;3.02345;,
 2.02226;-1.31884;2.14741;,
 -2.02194;-13.24183;-2.08246;,
 0.00016;-13.24183;-2.95849;,
 -2.85953;-13.24183;0.03248;,
 0.00016;-13.24183;-2.95849;,
 2.02226;-13.24183;-2.08246;,
 -2.02194;-13.24183;2.14741;,
 2.85984;-13.24183;0.03248;,
 0.00016;-13.24183;3.02345;,
 2.02226;-13.24183;2.14741;;
 
 40;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 3;15,16,14;,
 3;17,18,19;,
 3;20,19,21;,
 3;22,21,23;,
 3;24,23,25;,
 3;26,25,27;,
 3;28,27,29;,
 3;30,29,31;,
 3;32,31,33;,
 4;34,14,16,35;,
 4;34,36,12,14;,
 4;37,2,1,38;,
 4;36,39,10,12;,
 4;38,1,4,40;,
 4;39,41,8,10;,
 4;40,4,6,42;,
 4;41,42,6,8;,
 4;43,34,35,44;,
 4;43,44,33,31;,
 4;43,31,29,45;,
 4;43,45,36,34;,
 4;46,37,38,47;,
 4;46,47,19,18;,
 4;45,29,27,48;,
 4;45,48,39,36;,
 4;47,38,40,49;,
 4;47,49,21,19;,
 4;48,27,25,50;,
 4;48,50,41,39;,
 4;49,40,42,51;,
 4;49,51,23,21;,
 4;50,25,23,51;,
 4;50,51,42,41;;
 
 MeshMaterialList {
  1;
  40;
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
   0.040800;0.323200;0.091200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  34;
  0.000000;1.000000;0.000000;,
  0.000000;0.914010;-0.405693;,
  0.296175;0.911466;-0.285500;,
  0.416852;0.908974;0.000000;,
  0.296176;0.911466;0.285500;,
  -0.000000;0.914010;0.405692;,
  -0.296176;0.911465;0.285501;,
  -0.416852;0.908975;0.000000;,
  -0.296175;0.911466;-0.285501;,
  0.000000;-1.000000;0.000000;,
  -0.673898;0.348594;-0.651416;,
  0.000000;0.354573;-0.935029;,
  -0.939380;0.342878;0.000001;,
  0.673899;0.348595;-0.651415;,
  -0.673899;0.348594;0.651416;,
  0.939380;0.342878;0.000001;,
  -0.000000;0.354573;0.935028;,
  0.673901;0.348594;0.651414;,
  -0.690467;-0.277835;-0.667879;,
  0.000000;-0.283163;-0.959072;,
  -0.962089;-0.272737;0.000001;,
  0.690468;-0.277836;-0.667878;,
  -0.690467;-0.277835;0.667879;,
  0.962089;-0.272737;0.000001;,
  0.000000;-0.283163;0.959072;,
  0.690468;-0.277836;0.667878;,
  0.000000;-0.537417;-0.843317;,
  -0.610593;-0.528741;-0.589584;,
  -0.853971;-0.520320;0.000000;,
  0.610593;-0.528741;-0.589583;,
  -0.610593;-0.528740;0.589585;,
  0.853971;-0.520321;0.000000;,
  0.000000;-0.537417;0.843317;,
  0.610593;-0.528741;0.589584;;
  40;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,1,8;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  4;10,8,1,11;,
  4;10,12,7,8;,
  4;11,1,2,13;,
  4;12,14,6,7;,
  4;13,2,3,15;,
  4;14,16,5,6;,
  4;15,3,4,17;,
  4;16,17,4,5;,
  4;18,10,11,19;,
  4;18,19,26,27;,
  4;18,27,28,20;,
  4;18,20,12,10;,
  4;19,11,13,21;,
  4;19,21,29,26;,
  4;20,28,30,22;,
  4;20,22,14,12;,
  4;21,13,15,23;,
  4;21,23,31,29;,
  4;22,30,32,24;,
  4;22,24,16,14;,
  4;23,15,17,25;,
  4;23,25,33,31;,
  4;24,32,33,25;,
  4;24,25,17,16;;
 }
 MeshTextureCoords {
  52;
  0.062500;0.000000;,
  0.125000;0.000000;,
  0.000000;0.000000;,
  0.187500;0.000000;,
  0.250000;0.000000;,
  0.312500;0.000000;,
  0.375000;0.000000;,
  0.437500;0.000000;,
  0.500000;0.000000;,
  0.562500;0.000000;,
  0.625000;0.000000;,
  0.687500;0.000000;,
  0.750000;0.000000;,
  0.812500;0.000000;,
  0.875000;0.000000;,
  0.937500;0.000000;,
  1.000000;0.000000;,
  0.062500;1.000000;,
  0.000000;1.000000;,
  0.125000;1.000000;,
  0.187500;1.000000;,
  0.250000;1.000000;,
  0.312500;1.000000;,
  0.375000;1.000000;,
  0.437500;1.000000;,
  0.500000;1.000000;,
  0.562500;1.000000;,
  0.625000;1.000000;,
  0.687500;1.000000;,
  0.750000;1.000000;,
  0.812500;1.000000;,
  0.875000;1.000000;,
  0.937500;1.000000;,
  1.000000;1.000000;,
  0.875000;0.048440;,
  1.000000;0.048440;,
  0.750000;0.048440;,
  0.000000;0.048440;,
  0.125000;0.048440;,
  0.625000;0.048440;,
  0.250000;0.048440;,
  0.500000;0.048440;,
  0.375000;0.048440;,
  0.875000;0.939870;,
  1.000000;0.939870;,
  0.750000;0.939870;,
  0.000000;0.939870;,
  0.125000;0.939870;,
  0.625000;0.939870;,
  0.250000;0.939870;,
  0.500000;0.939870;,
  0.375000;0.939870;;
 }
}
