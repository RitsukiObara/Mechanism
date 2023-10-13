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
 45;
 -7.75408;-3.63040;-2.95051;,
 0.00000;-3.63040;-2.95051;,
 0.00000;-6.12043;-2.45872;,
 -7.36638;-4.83905;-2.79174;,
 0.00000;0.00010;2.80861;,
 -8.06973;0.00010;2.69966;,
 -7.75408;-3.63040;2.80861;,
 0.00000;-3.63040;2.80861;,
 -7.36638;-4.83905;2.64983;,
 0.00000;-6.12043;2.80861;,
 0.00000;0.00010;-0.36685;,
 0.00000;0.00010;-2.95051;,
 -8.06973;0.00010;-2.84156;,
 -8.35644;0.00010;-0.36685;,
 -8.06973;0.00010;2.69966;,
 -8.35644;0.00010;-0.36685;,
 -8.06973;0.00010;-2.84156;,
 -7.75408;-3.63040;-2.95051;,
 -7.75408;-3.63040;-0.36685;,
 -7.75408;-3.63040;2.80861;,
 0.00000;-6.12043;-0.36685;,
 -7.36638;-4.83905;2.64983;,
 -7.75408;-4.83905;-0.36685;,
 -7.36638;-4.83905;-2.79174;,
 0.00000;-6.12043;-2.45872;,
 -7.36638;-4.83905;-2.79174;,
 -7.75408;-4.83905;-0.36685;,
 7.36638;-4.83905;-2.79174;,
 7.75408;-3.63040;-2.95051;,
 7.75408;-3.63040;2.80861;,
 8.06973;0.00010;2.69966;,
 7.36638;-4.83905;2.64983;,
 8.35644;0.00010;-0.36685;,
 8.06973;0.00010;-2.84156;,
 8.06973;0.00010;2.69966;,
 7.75408;-3.63040;-0.36685;,
 7.75408;-3.63040;-2.95051;,
 8.06973;0.00010;-2.84156;,
 8.35644;0.00010;-0.36685;,
 7.75408;-3.63040;2.80861;,
 7.75408;-4.83905;-0.36685;,
 7.36638;-4.83905;2.64983;,
 7.36638;-4.83905;-2.79174;,
 7.75408;-4.83905;-0.36685;,
 7.36638;-4.83905;-2.79174;;
 
 24;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;7,6,8,9;,
 4;10,11,12,13;,
 4;10,13,14,4;,
 4;15,16,17,18;,
 4;15,18,19,14;,
 4;20,9,21,22;,
 4;20,22,23,24;,
 4;18,17,25,26;,
 4;18,26,21,19;,
 4;16,11,1,0;,
 4;27,2,1,28;,
 4;7,29,30,4;,
 4;9,31,29,7;,
 4;32,33,11,10;,
 4;4,34,32,10;,
 4;35,36,37,38;,
 4;34,39,35,38;,
 4;40,41,9,20;,
 4;24,42,40,20;,
 4;43,44,36,35;,
 4;39,41,43,35;,
 4;28,1,11,37;;
 
 MeshMaterialList {
  1;
  24;
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
  46;
  0.000000;1.000000;0.000000;,
  -0.000714;-0.074127;-0.997249;,
  0.000000;-0.074127;-0.997249;,
  0.005326;-0.162082;-0.986763;,
  0.000000;-0.162085;-0.986777;,
  0.000000;0.014413;0.999896;,
  0.000000;-0.025449;0.999676;,
  0.000000;-0.065272;0.997868;,
  -0.006748;0.014412;0.999873;,
  -0.008780;-0.025448;0.999638;,
  -0.010798;-0.065268;0.997809;,
  0.000000;-0.999999;-0.001296;,
  -0.990092;-0.140264;-0.006617;,
  -0.167211;-0.985920;-0.001278;,
  0.000714;-0.074127;-0.997249;,
  -0.005326;-0.162082;-0.986763;,
  0.006748;0.014412;0.999873;,
  0.008780;-0.025448;0.999638;,
  0.010798;-0.065268;0.997809;,
  0.990092;-0.140264;-0.006617;,
  0.167211;-0.985920;-0.001278;,
  -0.992124;-0.125137;-0.005460;,
  -0.990534;-0.124915;-0.056912;,
  -0.987775;-0.140010;-0.068541;,
  -0.988607;-0.139980;0.055332;,
  -0.991086;-0.125028;0.046006;,
  0.000000;-0.999943;0.010625;,
  -0.167202;-0.985867;0.010475;,
  -0.167197;-0.985837;-0.013031;,
  0.000000;-0.999913;-0.013217;,
  -0.984650;-0.155054;-0.080145;,
  -0.987824;-0.155378;-0.007773;,
  -0.985815;-0.154887;0.064639;,
  -0.006748;0.014412;-0.999873;,
  0.000000;0.014413;-0.999896;,
  0.987775;-0.140010;-0.068541;,
  0.990534;-0.124915;-0.056912;,
  0.992124;-0.125137;-0.005460;,
  0.991086;-0.125028;0.046006;,
  0.988607;-0.139980;0.055332;,
  0.167202;-0.985867;0.010475;,
  0.167197;-0.985837;-0.013031;,
  0.987824;-0.155378;-0.007773;,
  0.984650;-0.155054;-0.080145;,
  0.985815;-0.154887;0.064639;,
  0.006748;0.014412;-0.999873;;
  24;
  4;1,2,4,3;,
  4;5,8,9,6;,
  4;6,9,10,7;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;21,22,23,12;,
  4;21,12,24,25;,
  4;11,26,27,13;,
  4;11,13,28,29;,
  4;12,23,30,31;,
  4;12,31,32,24;,
  4;33,34,2,1;,
  4;15,4,2,14;,
  4;6,17,16,5;,
  4;7,18,17,6;,
  4;0,0,0,0;,
  4;0,0,0,0;,
  4;19,35,36,37;,
  4;38,39,19,37;,
  4;20,40,26,11;,
  4;29,41,20,11;,
  4;42,43,35,19;,
  4;39,44,42,19;,
  4;14,2,34,45;;
 }
 MeshTextureCoords {
  45;
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.500000;0.500000;,
  1.000000;1.000000;,
  0.500000;1.000000;,
  0.500000;0.500000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.500000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.500000;,
  0.500000;0.500000;,
  0.000000;0.500000;,
  0.500000;0.500000;,
  0.000000;1.000000;,
  0.000000;0.500000;,
  0.000000;0.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.500000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.500000;,
  1.000000;0.500000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.500000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;0.500000;,
  1.000000;0.500000;,
  1.000000;0.000000;,
  0.500000;0.000000;,
  0.000000;0.500000;,
  0.000000;0.500000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.500000;1.000000;,
  1.000000;1.000000;;
 }
}
