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
 0.00028;0.00023;-4.46415;,
 -3.01779;0.00023;-3.15663;,
 0.00028;0.00023;0.00000;,
 -4.26789;0.00023;0.00000;,
 0.00028;0.00023;0.00000;,
 -3.01779;0.00023;3.15663;,
 0.00028;0.00023;0.00000;,
 0.00030;0.00023;4.46415;,
 0.00028;0.00023;0.00000;,
 3.01836;0.00023;3.15663;,
 0.00028;0.00023;0.00000;,
 4.26849;0.00023;0.00000;,
 0.00028;0.00023;0.00000;,
 3.01836;0.00023;-3.15663;,
 0.00028;0.00023;0.00000;,
 0.00028;0.00023;-4.46415;,
 0.00028;0.00023;0.00000;,
 -3.61152;-27.73888;-3.77747;,
 0.00015;-27.73888;-5.34216;,
 0.00015;-27.73888;-0.00000;,
 -5.10750;-27.73888;0.00000;,
 0.00015;-27.73888;-0.00000;,
 -3.61152;-27.73888;3.77747;,
 0.00015;-27.73888;-0.00000;,
 0.00015;-27.73888;5.34216;,
 0.00015;-27.73888;-0.00000;,
 3.61181;-27.73888;3.77747;,
 0.00015;-27.73888;-0.00000;,
 5.10782;-27.73888;-0.00000;,
 0.00015;-27.73888;-0.00000;,
 3.61181;-27.73888;-3.77747;,
 0.00015;-27.73888;-0.00000;,
 0.00015;-27.73888;-5.34216;,
 0.00015;-27.73888;-0.00000;,
 -4.07077;-23.48004;-4.25781;,
 0.00015;-23.48004;-6.02147;,
 4.07108;-23.48004;-4.25781;,
 0.00015;-23.48004;-6.02147;,
 -5.75698;-23.48004;0.00000;,
 5.75732;-23.48004;-0.00000;,
 -4.07077;-23.48004;4.25781;,
 4.07108;-23.48004;4.25781;,
 0.00015;-23.48004;6.02147;,
 -4.07065;-2.11635;-4.25781;,
 0.00027;-2.11635;-6.02147;,
 4.07120;-2.11635;-4.25781;,
 0.00027;-2.11635;-6.02147;,
 -5.75685;-2.11635;0.00000;,
 5.75744;-2.11635;-0.00000;,
 -4.07065;-2.11635;4.25781;,
 4.07120;-2.11635;4.25781;,
 0.00027;-2.11635;6.02147;;
 
 40;
 3;0,1,2;,
 3;1,3,4;,
 3;3,5,6;,
 3;5,7,8;,
 3;7,9,10;,
 3;9,11,12;,
 3;11,13,14;,
 3;13,15,16;,
 3;17,18,19;,
 3;20,17,21;,
 3;22,20,23;,
 3;24,22,25;,
 3;26,24,27;,
 3;28,26,29;,
 3;30,28,31;,
 3;32,30,33;,
 4;18,17,34,35;,
 4;36,30,32,37;,
 4;17,20,38,34;,
 4;39,28,30,36;,
 4;20,22,40,38;,
 4;41,26,28,39;,
 4;22,24,42,40;,
 4;42,24,26,41;,
 4;43,1,0,44;,
 4;35,34,43,44;,
 4;45,36,37,46;,
 4;15,13,45,46;,
 4;47,3,1,43;,
 4;34,38,47,43;,
 4;48,39,36,45;,
 4;13,11,48,45;,
 4;49,5,3,47;,
 4;38,40,49,47;,
 4;50,41,39,48;,
 4;11,9,50,48;,
 4;51,7,5,49;,
 4;40,42,51,49;,
 4;51,42,41,50;,
 4;9,7,51,50;;
 
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
   0.276000;0.276000;0.276000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  34;
  0.000000;1.000000;0.000000;,
  0.000000;0.898828;-0.438302;,
  -0.319438;0.896083;-0.308212;,
  -0.449249;0.893406;0.000000;,
  -0.319438;0.896083;0.308211;,
  0.000001;0.898827;0.438302;,
  0.319440;0.896081;0.308215;,
  0.449251;0.893406;0.000000;,
  0.319439;0.896082;-0.308215;,
  0.000000;-1.000000;-0.000000;,
  0.000000;-0.079082;-0.996868;,
  -0.716137;-0.077329;-0.693663;,
  0.716134;-0.077334;-0.693665;,
  -0.997134;-0.075651;0.000000;,
  0.997134;-0.075659;-0.000000;,
  -0.716137;-0.077329;0.693663;,
  0.716134;-0.077334;0.693665;,
  0.000000;-0.079082;0.996868;,
  0.000000;0.316323;-0.948651;,
  -0.683311;0.310648;-0.660745;,
  0.683310;0.310641;-0.660750;,
  -0.952284;0.305214;0.000000;,
  0.952286;0.305206;0.000000;,
  -0.683311;0.310648;0.660745;,
  0.683310;0.310640;0.660749;,
  0.000001;0.316323;0.948651;,
  0.000000;-0.157514;-0.987517;,
  -0.709758;-0.154066;-0.687392;,
  0.709755;-0.154068;-0.687394;,
  -0.988570;-0.150760;0.000000;,
  0.988570;-0.150763;-0.000000;,
  -0.709758;-0.154066;0.687392;,
  0.709755;-0.154068;0.687394;,
  0.000000;-0.157514;0.987517;;
  40;
  3;1,2,0;,
  3;2,3,0;,
  3;3,4,0;,
  3;4,5,0;,
  3;5,6,0;,
  3;6,7,0;,
  3;7,8,0;,
  3;8,1,0;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  4;26,27,11,10;,
  4;12,28,26,10;,
  4;27,29,13,11;,
  4;14,30,28,12;,
  4;29,31,15,13;,
  4;16,32,30,14;,
  4;31,33,17,15;,
  4;17,33,32,16;,
  4;19,2,1,18;,
  4;10,11,19,18;,
  4;20,12,10,18;,
  4;1,8,20,18;,
  4;21,3,2,19;,
  4;11,13,21,19;,
  4;22,14,12,20;,
  4;8,7,22,20;,
  4;23,4,3,21;,
  4;13,15,23,21;,
  4;24,16,14,22;,
  4;7,6,24,22;,
  4;25,5,4,23;,
  4;15,17,25,23;,
  4;25,17,16,24;,
  4;6,5,25,24;;
 }
 MeshTextureCoords {
  52;
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.062500;0.000000;,
  0.250000;0.000000;,
  0.187500;0.000000;,
  0.375000;0.000000;,
  0.312500;0.000000;,
  0.500000;0.000000;,
  0.437500;0.000000;,
  0.625000;0.000000;,
  0.562500;0.000000;,
  0.750000;0.000000;,
  0.687500;0.000000;,
  0.875000;0.000000;,
  0.812500;0.000000;,
  1.000000;0.000000;,
  0.937500;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.062500;1.000000;,
  0.250000;1.000000;,
  0.187500;1.000000;,
  0.375000;1.000000;,
  0.312500;1.000000;,
  0.500000;1.000000;,
  0.437500;1.000000;,
  0.625000;1.000000;,
  0.562500;1.000000;,
  0.750000;1.000000;,
  0.687500;1.000000;,
  0.875000;1.000000;,
  0.812500;1.000000;,
  1.000000;1.000000;,
  0.937500;1.000000;,
  0.125000;0.965230;,
  0.000000;0.965230;,
  0.875000;0.965230;,
  1.000000;0.965230;,
  0.250000;0.965230;,
  0.750000;0.965230;,
  0.375000;0.965230;,
  0.625000;0.965230;,
  0.500000;0.965230;,
  0.125000;0.087010;,
  0.000000;0.087010;,
  0.875000;0.087010;,
  1.000000;0.087010;,
  0.250000;0.087010;,
  0.750000;0.087010;,
  0.375000;0.087010;,
  0.625000;0.087010;,
  0.500000;0.087010;;
 }
}