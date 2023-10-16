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
 65;
 0.00000;-7.73520;0.00204;,
 0.00000;-6.86076;-2.09656;,
 1.04928;-6.86076;-1.81540;,
 1.81740;-6.86076;-1.04728;,
 2.09852;-6.86076;0.00200;,
 1.81740;-6.86076;1.05124;,
 1.04928;-6.86076;1.81936;,
 0.00000;-6.86076;2.10052;,
 -1.04928;-6.86076;1.81936;,
 -1.81740;-6.86076;1.05124;,
 -2.09852;-6.86076;0.00200;,
 -1.81740;-6.86076;-1.04728;,
 -1.04928;-6.86076;-1.81540;,
 1.81740;6.19272;-1.04864;,
 4.29548;7.73712;-2.48000;,
 4.96000;7.73712;0.00000;,
 2.09852;6.19272;0.00064;,
 2.09852;-6.86076;0.00200;,
 1.81740;-6.86076;-1.04728;,
 1.04928;-6.86076;-1.81540;,
 1.04928;6.19272;-1.81676;,
 2.48000;7.73712;-4.29548;,
 4.29548;7.73712;2.48000;,
 1.81740;6.19272;1.04988;,
 1.81740;-6.86076;1.05124;,
 0.00000;-6.86076;-2.09656;,
 0.00000;6.19272;-2.09792;,
 0.00000;7.73712;-4.96000;,
 2.48000;7.73712;4.29548;,
 1.04928;6.19272;1.81800;,
 1.04928;-6.86076;1.81936;,
 0.00000;6.19272;-2.09792;,
 0.00000;-6.86076;-2.09656;,
 -1.04928;-6.86076;-1.81540;,
 -1.04928;6.19272;-1.81676;,
 -2.48000;7.73712;-4.29548;,
 0.00000;7.73712;-4.96000;,
 0.00000;7.73712;4.96000;,
 0.00000;6.19272;2.09916;,
 0.00000;-6.86076;2.10052;,
 -1.81740;-6.86076;-1.04728;,
 -1.81740;6.19272;-1.04864;,
 -4.29548;7.73712;-2.48000;,
 -2.48000;7.73712;4.29548;,
 -1.04928;6.19272;1.81800;,
 -1.04928;-6.86076;1.81936;,
 -2.09852;-6.86076;0.00200;,
 -2.09852;6.19272;0.00064;,
 -4.96000;7.73712;0.00000;,
 -4.29548;7.73712;2.48000;,
 -1.81740;6.19272;1.04988;,
 -1.81740;-6.86076;1.05124;,
 0.00000;7.73652;0.00000;,
 2.48000;7.73712;-4.29548;,
 0.00000;7.73712;-4.96000;,
 4.29548;7.73712;-2.48000;,
 4.96000;7.73712;0.00000;,
 4.29548;7.73712;2.48000;,
 2.48000;7.73712;4.29548;,
 0.00000;7.73712;4.96000;,
 -2.48000;7.73712;4.29548;,
 -4.29548;7.73712;2.48000;,
 -4.96000;7.73712;0.00000;,
 -4.29548;7.73712;-2.48000;,
 -2.48000;7.73712;-4.29548;;
 
 48;
 3;0,1,2;,
 3;0,2,3;,
 3;0,3,4;,
 3;0,4,5;,
 3;0,5,6;,
 3;0,6,7;,
 3;0,7,8;,
 3;0,8,9;,
 3;0,9,10;,
 3;0,10,11;,
 3;0,11,12;,
 3;0,12,1;,
 4;13,14,15,16;,
 4;13,16,17,18;,
 4;13,18,19,20;,
 4;13,20,21,14;,
 4;16,15,22,23;,
 4;16,23,24,17;,
 4;20,19,25,26;,
 4;20,26,27,21;,
 4;23,22,28,29;,
 4;23,29,30,24;,
 4;31,32,33,34;,
 4;31,34,35,36;,
 4;29,28,37,38;,
 4;29,38,39,30;,
 4;34,33,40,41;,
 4;34,41,42,35;,
 4;38,37,43,44;,
 4;38,44,45,39;,
 4;41,40,46,47;,
 4;41,47,48,42;,
 4;44,43,49,50;,
 4;44,50,51,45;,
 4;47,46,51,50;,
 4;47,50,49,48;,
 3;52,53,54;,
 3;52,55,53;,
 3;52,56,55;,
 3;52,57,56;,
 3;52,58,57;,
 3;52,59,58;,
 3;52,60,59;,
 3;52,61,60;,
 3;52,62,61;,
 3;52,63,62;,
 3;52,64,63;,
 3;52,54,64;;
 
 MeshMaterialList {
  3;
  48;
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
  1,
  0,
  0,
  1,
  1,
  0,
  0,
  1,
  1,
  0,
  0,
  1,
  1,
  0,
  0,
  1,
  1,
  0,
  0,
  1,
  1,
  0,
  0,
  1,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2,
  2;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\Screw.png";
   }
  }
  Material {
   0.605600;0.605600;0.605600;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\ScrewHead.png";
   }
  }
 }
 MeshNormals {
  50;
  -0.000000;-1.000000;0.000006;,
  0.000000;-0.923073;-0.384624;,
  0.192314;-0.923073;-0.333095;,
  0.333101;-0.923072;-0.192308;,
  0.384637;-0.923068;0.000002;,
  0.333108;-0.923068;0.192316;,
  0.192322;-0.923066;0.333109;,
  0.000000;-0.923065;0.384643;,
  -0.192322;-0.923066;0.333109;,
  -0.333108;-0.923068;0.192316;,
  -0.384637;-0.923068;0.000002;,
  -0.333101;-0.923072;-0.192308;,
  -0.192314;-0.923073;-0.333095;,
  0.411297;-0.880029;-0.237453;,
  0.474961;-0.880007;0.000007;,
  0.500002;-0.000090;-0.866024;,
  0.411361;-0.879986;0.237503;,
  0.000000;-0.000104;-1.000000;,
  0.237514;-0.879969;0.411390;,
  -0.500002;-0.000090;-0.866024;,
  0.000000;-0.879964;0.475041;,
  -0.866033;-0.000052;-0.499987;,
  -0.237514;-0.879969;0.411390;,
  -1.000000;0.000000;0.000005;,
  -0.411361;-0.879986;0.237503;,
  0.000000;1.000000;0.000000;,
  0.000000;-0.880050;-0.474881;,
  0.237450;-0.880044;-0.411267;,
  -0.474961;-0.880007;0.000007;,
  -0.411297;-0.880029;-0.237453;,
  -0.237450;-0.880044;-0.411267;,
  0.866033;-0.000052;-0.499987;,
  1.000000;0.000000;0.000005;,
  0.866030;0.000052;0.499991;,
  0.500002;0.000090;0.866024;,
  0.000000;0.000104;1.000000;,
  -0.500002;0.000090;0.866024;,
  -0.866030;0.000052;0.499991;,
  -0.000061;1.000000;0.000105;,
  0.000000;1.000000;0.000121;,
  -0.000105;1.000000;0.000061;,
  -0.000121;1.000000;0.000000;,
  -0.000105;1.000000;-0.000061;,
  -0.000061;1.000000;-0.000105;,
  0.000000;1.000000;-0.000121;,
  0.000061;1.000000;-0.000105;,
  0.000105;1.000000;-0.000061;,
  0.000121;1.000000;0.000000;,
  0.000105;1.000000;0.000061;,
  0.000061;1.000000;0.000105;;
  48;
  3;0,1,2;,
  3;0,2,3;,
  3;0,3,4;,
  3;0,4,5;,
  3;0,5,6;,
  3;0,6,7;,
  3;0,7,8;,
  3;0,8,9;,
  3;0,9,10;,
  3;0,10,11;,
  3;0,11,12;,
  3;0,12,1;,
  4;13,13,14,14;,
  4;31,32,32,31;,
  4;31,31,15,15;,
  4;13,27,27,13;,
  4;14,14,16,16;,
  4;32,33,33,32;,
  4;15,15,17,17;,
  4;27,26,26,27;,
  4;16,16,18,18;,
  4;33,34,34,33;,
  4;17,17,19,19;,
  4;26,30,30,26;,
  4;18,18,20,20;,
  4;34,35,35,34;,
  4;19,19,21,21;,
  4;30,29,29,30;,
  4;20,20,22,22;,
  4;35,36,36,35;,
  4;21,21,23,23;,
  4;29,28,28,29;,
  4;22,22,24,24;,
  4;36,37,37,36;,
  4;23,23,37,37;,
  4;28,24,24,28;,
  3;25,38,39;,
  3;25,40,38;,
  3;25,41,40;,
  3;25,42,41;,
  3;25,43,42;,
  3;25,44,43;,
  3;25,45,44;,
  3;25,46,45;,
  3;25,47,46;,
  3;25,48,47;,
  3;25,49,48;,
  3;25,39,49;;
 }
 MeshTextureCoords {
  65;
  0.500000;0.690050;,
  0.000000;0.690050;,
  0.083420;0.690050;,
  0.166810;0.690050;,
  0.250170;0.690050;,
  0.333480;0.690050;,
  0.416750;0.690050;,
  0.500000;0.690050;,
  0.583250;0.690050;,
  0.666520;0.690050;,
  0.749830;0.690050;,
  0.833190;0.690050;,
  0.916580;0.690050;,
  0.166670;-1.727550;,
  0.166670;-1.811520;,
  0.250000;-1.811520;,
  0.250000;-1.727550;,
  0.250110;0.635850;,
  0.166760;0.635850;,
  0.083390;0.635850;,
  0.083330;-1.727550;,
  0.083330;-1.811520;,
  0.333330;-1.811520;,
  0.333330;-1.727550;,
  0.333430;0.635850;,
  0.000000;0.635850;,
  0.000000;-1.727550;,
  0.000000;-1.811520;,
  0.416670;-1.811520;,
  0.416670;-1.727550;,
  0.416720;0.635850;,
  1.000000;-1.727550;,
  1.000000;0.635850;,
  0.916610;0.635850;,
  0.916670;-1.727550;,
  0.916670;-1.811520;,
  1.000000;-1.811520;,
  0.500000;-1.811520;,
  0.500000;-1.727550;,
  0.500000;0.635850;,
  0.833240;0.635850;,
  0.833330;-1.727550;,
  0.833330;-1.811520;,
  0.583330;-1.811520;,
  0.583330;-1.727550;,
  0.583280;0.635850;,
  0.749890;0.635850;,
  0.750000;-1.727550;,
  0.750000;-1.811520;,
  0.666670;-1.811520;,
  0.666670;-1.727550;,
  0.666570;0.635850;,
  0.500270;0.505580;,
  0.738650;0.918480;,
  0.500260;0.982340;,
  0.913160;0.743970;,
  0.977050;0.505590;,
  0.913180;0.267210;,
  0.738670;0.092690;,
  0.500290;0.028810;,
  0.261900;0.092680;,
  0.087380;0.267180;,
  0.023500;0.505560;,
  0.087370;0.743950;,
  0.261880;0.918460;;
 }
}