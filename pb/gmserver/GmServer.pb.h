// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: GmServer.proto

#ifndef PROTOBUF_GmServer_2eproto__INCLUDED
#define PROTOBUF_GmServer_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2005000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2005000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace gmserver {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_GmServer_2eproto();
void protobuf_AssignDesc_GmServer_2eproto();
void protobuf_ShutdownFile_GmServer_2eproto();

class Heartbeat;
class LoginInfo;

// ===================================================================

class Heartbeat : public ::google::protobuf::Message {
 public:
  Heartbeat();
  virtual ~Heartbeat();

  Heartbeat(const Heartbeat& from);

  inline Heartbeat& operator=(const Heartbeat& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const Heartbeat& default_instance();

  void Swap(Heartbeat* other);

  // implements Message ----------------------------------------------

  Heartbeat* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const Heartbeat& from);
  void MergeFrom(const Heartbeat& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required uint32 recode = 1;
  inline bool has_recode() const;
  inline void clear_recode();
  static const int kRecodeFieldNumber = 1;
  inline ::google::protobuf::uint32 recode() const;
  inline void set_recode(::google::protobuf::uint32 value);

  // required uint32 seq = 2;
  inline bool has_seq() const;
  inline void clear_seq();
  static const int kSeqFieldNumber = 2;
  inline ::google::protobuf::uint32 seq() const;
  inline void set_seq(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:gmserver.Heartbeat)
 private:
  inline void set_has_recode();
  inline void clear_has_recode();
  inline void set_has_seq();
  inline void clear_has_seq();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 recode_;
  ::google::protobuf::uint32 seq_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];

  friend void  protobuf_AddDesc_GmServer_2eproto();
  friend void protobuf_AssignDesc_GmServer_2eproto();
  friend void protobuf_ShutdownFile_GmServer_2eproto();

  void InitAsDefaultInstance();
  static Heartbeat* default_instance_;
};
// -------------------------------------------------------------------

class LoginInfo : public ::google::protobuf::Message {
 public:
  LoginInfo();
  virtual ~LoginInfo();

  LoginInfo(const LoginInfo& from);

  inline LoginInfo& operator=(const LoginInfo& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const LoginInfo& default_instance();

  void Swap(LoginInfo* other);

  // implements Message ----------------------------------------------

  LoginInfo* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const LoginInfo& from);
  void MergeFrom(const LoginInfo& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required string user_id = 1;
  inline bool has_user_id() const;
  inline void clear_user_id();
  static const int kUserIdFieldNumber = 1;
  inline const ::std::string& user_id() const;
  inline void set_user_id(const ::std::string& value);
  inline void set_user_id(const char* value);
  inline void set_user_id(const char* value, size_t size);
  inline ::std::string* mutable_user_id();
  inline ::std::string* release_user_id();
  inline void set_allocated_user_id(::std::string* user_id);

  // required string user_pwd = 2;
  inline bool has_user_pwd() const;
  inline void clear_user_pwd();
  static const int kUserPwdFieldNumber = 2;
  inline const ::std::string& user_pwd() const;
  inline void set_user_pwd(const ::std::string& value);
  inline void set_user_pwd(const char* value);
  inline void set_user_pwd(const char* value, size_t size);
  inline ::std::string* mutable_user_pwd();
  inline ::std::string* release_user_pwd();
  inline void set_allocated_user_pwd(::std::string* user_pwd);

  // @@protoc_insertion_point(class_scope:gmserver.LoginInfo)
 private:
  inline void set_has_user_id();
  inline void clear_has_user_id();
  inline void set_has_user_pwd();
  inline void clear_has_user_pwd();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::std::string* user_id_;
  ::std::string* user_pwd_;

  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];

  friend void  protobuf_AddDesc_GmServer_2eproto();
  friend void protobuf_AssignDesc_GmServer_2eproto();
  friend void protobuf_ShutdownFile_GmServer_2eproto();

  void InitAsDefaultInstance();
  static LoginInfo* default_instance_;
};
// ===================================================================


// ===================================================================

// Heartbeat

// required uint32 recode = 1;
inline bool Heartbeat::has_recode() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void Heartbeat::set_has_recode() {
  _has_bits_[0] |= 0x00000001u;
}
inline void Heartbeat::clear_has_recode() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void Heartbeat::clear_recode() {
  recode_ = 0u;
  clear_has_recode();
}
inline ::google::protobuf::uint32 Heartbeat::recode() const {
  return recode_;
}
inline void Heartbeat::set_recode(::google::protobuf::uint32 value) {
  set_has_recode();
  recode_ = value;
}

// required uint32 seq = 2;
inline bool Heartbeat::has_seq() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void Heartbeat::set_has_seq() {
  _has_bits_[0] |= 0x00000002u;
}
inline void Heartbeat::clear_has_seq() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void Heartbeat::clear_seq() {
  seq_ = 0u;
  clear_has_seq();
}
inline ::google::protobuf::uint32 Heartbeat::seq() const {
  return seq_;
}
inline void Heartbeat::set_seq(::google::protobuf::uint32 value) {
  set_has_seq();
  seq_ = value;
}

// -------------------------------------------------------------------

// LoginInfo

// required string user_id = 1;
inline bool LoginInfo::has_user_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void LoginInfo::set_has_user_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void LoginInfo::clear_has_user_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void LoginInfo::clear_user_id() {
  if (user_id_ != &::google::protobuf::internal::kEmptyString) {
    user_id_->clear();
  }
  clear_has_user_id();
}
inline const ::std::string& LoginInfo::user_id() const {
  return *user_id_;
}
inline void LoginInfo::set_user_id(const ::std::string& value) {
  set_has_user_id();
  if (user_id_ == &::google::protobuf::internal::kEmptyString) {
    user_id_ = new ::std::string;
  }
  user_id_->assign(value);
}
inline void LoginInfo::set_user_id(const char* value) {
  set_has_user_id();
  if (user_id_ == &::google::protobuf::internal::kEmptyString) {
    user_id_ = new ::std::string;
  }
  user_id_->assign(value);
}
inline void LoginInfo::set_user_id(const char* value, size_t size) {
  set_has_user_id();
  if (user_id_ == &::google::protobuf::internal::kEmptyString) {
    user_id_ = new ::std::string;
  }
  user_id_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* LoginInfo::mutable_user_id() {
  set_has_user_id();
  if (user_id_ == &::google::protobuf::internal::kEmptyString) {
    user_id_ = new ::std::string;
  }
  return user_id_;
}
inline ::std::string* LoginInfo::release_user_id() {
  clear_has_user_id();
  if (user_id_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = user_id_;
    user_id_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void LoginInfo::set_allocated_user_id(::std::string* user_id) {
  if (user_id_ != &::google::protobuf::internal::kEmptyString) {
    delete user_id_;
  }
  if (user_id) {
    set_has_user_id();
    user_id_ = user_id;
  } else {
    clear_has_user_id();
    user_id_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}

// required string user_pwd = 2;
inline bool LoginInfo::has_user_pwd() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void LoginInfo::set_has_user_pwd() {
  _has_bits_[0] |= 0x00000002u;
}
inline void LoginInfo::clear_has_user_pwd() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void LoginInfo::clear_user_pwd() {
  if (user_pwd_ != &::google::protobuf::internal::kEmptyString) {
    user_pwd_->clear();
  }
  clear_has_user_pwd();
}
inline const ::std::string& LoginInfo::user_pwd() const {
  return *user_pwd_;
}
inline void LoginInfo::set_user_pwd(const ::std::string& value) {
  set_has_user_pwd();
  if (user_pwd_ == &::google::protobuf::internal::kEmptyString) {
    user_pwd_ = new ::std::string;
  }
  user_pwd_->assign(value);
}
inline void LoginInfo::set_user_pwd(const char* value) {
  set_has_user_pwd();
  if (user_pwd_ == &::google::protobuf::internal::kEmptyString) {
    user_pwd_ = new ::std::string;
  }
  user_pwd_->assign(value);
}
inline void LoginInfo::set_user_pwd(const char* value, size_t size) {
  set_has_user_pwd();
  if (user_pwd_ == &::google::protobuf::internal::kEmptyString) {
    user_pwd_ = new ::std::string;
  }
  user_pwd_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* LoginInfo::mutable_user_pwd() {
  set_has_user_pwd();
  if (user_pwd_ == &::google::protobuf::internal::kEmptyString) {
    user_pwd_ = new ::std::string;
  }
  return user_pwd_;
}
inline ::std::string* LoginInfo::release_user_pwd() {
  clear_has_user_pwd();
  if (user_pwd_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = user_pwd_;
    user_pwd_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}
inline void LoginInfo::set_allocated_user_pwd(::std::string* user_pwd) {
  if (user_pwd_ != &::google::protobuf::internal::kEmptyString) {
    delete user_pwd_;
  }
  if (user_pwd) {
    set_has_user_pwd();
    user_pwd_ = user_pwd;
  } else {
    clear_has_user_pwd();
    user_pwd_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  }
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace gmserver

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_GmServer_2eproto__INCLUDED