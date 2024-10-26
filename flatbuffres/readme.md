# cpp コード生成
flatc --cpp ./schema/monster.fbs  

# makefile include path追加

https://github.com/google/flatbuffers/tree/master
をcloseした場所へinclude path指定する

-I/home/takashi/develop/flatbuffers/include

# Compie error

float_double_generated.h: In member function ‘bool Sample::TopTable::Verify(flatbuffers::Verifier&) const’:
float_double_generated.h:28:30: error: no matching function for call to ‘Sample::TopTable::VerifyField<float>(flatbuffers::Verifier&, Sample::TopTable::FlatBuffersVTableOffset) const’
   28 |            VerifyField<float>(verifier, VT_F_VAL) &&
      |            ~~~~~~~~~~~~~~~~~~^~~~~~~~~~~~~~~~~~~~
In file included from /home/takashi/develop/flatbuffers/include/flatbuffers/flatbuffer_builder.h:36,
                 from /home/takashi/develop/flatbuffers/include/flatbuffers/flatbuffers.h:29,
                 from float_double_generated.h:7,
                 from serialize.cpp:1:

# Compie error 修正

## 修正前
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<float>(verifier, VT_F_VAL) &&
           VerifyField<double>(verifier, VT_D_VAL) &&
           verifier.EndTable();
  }

## 修正跡
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<float>(verifier, VT_F_VAL, sizeof(float)) &&
           VerifyField<double>(verifier, VT_D_VAL, sizeof(double)) &&
           verifier.EndTable();
  }