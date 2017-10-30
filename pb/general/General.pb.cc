// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: General.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "General.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace generalmess {

namespace {

const ::google::protobuf::Descriptor* Heartbeat_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Heartbeat_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_General_2eproto() {
  protobuf_AddDesc_General_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "General.proto");
  GOOGLE_CHECK(file != NULL);
  Heartbeat_descriptor_ = file->message_type(0);
  static const int Heartbeat_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Heartbeat, recode_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Heartbeat, seq_),
  };
  Heartbeat_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Heartbeat_descriptor_,
      Heartbeat::default_instance_,
      Heartbeat_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Heartbeat, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Heartbeat, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Heartbeat));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_General_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Heartbeat_descriptor_, &Heartbeat::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_General_2eproto() {
  delete Heartbeat::default_instance_;
  delete Heartbeat_reflection_;
}

void protobuf_AddDesc_General_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\rGeneral.proto\022\013generalmess\"(\n\tHeartbea"
    "t\022\016\n\006recode\030\001 \002(\r\022\013\n\003seq\030\002 \002(\r", 70);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "General.proto", &protobuf_RegisterTypes);
  Heartbeat::default_instance_ = new Heartbeat();
  Heartbeat::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_General_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_General_2eproto {
  StaticDescriptorInitializer_General_2eproto() {
    protobuf_AddDesc_General_2eproto();
  }
} static_descriptor_initializer_General_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int Heartbeat::kRecodeFieldNumber;
const int Heartbeat::kSeqFieldNumber;
#endif  // !_MSC_VER

Heartbeat::Heartbeat()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void Heartbeat::InitAsDefaultInstance() {
}

Heartbeat::Heartbeat(const Heartbeat& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void Heartbeat::SharedCtor() {
  _cached_size_ = 0;
  recode_ = 0u;
  seq_ = 0u;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Heartbeat::~Heartbeat() {
  SharedDtor();
}

void Heartbeat::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Heartbeat::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Heartbeat::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Heartbeat_descriptor_;
}

const Heartbeat& Heartbeat::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_General_2eproto();
  return *default_instance_;
}

Heartbeat* Heartbeat::default_instance_ = NULL;

Heartbeat* Heartbeat::New() const {
  return new Heartbeat;
}

void Heartbeat::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    recode_ = 0u;
    seq_ = 0u;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Heartbeat::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required uint32 recode = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &recode_)));
          set_has_recode();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(16)) goto parse_seq;
        break;
      }

      // required uint32 seq = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_seq:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::uint32, ::google::protobuf::internal::WireFormatLite::TYPE_UINT32>(
                 input, &seq_)));
          set_has_seq();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void Heartbeat::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required uint32 recode = 1;
  if (has_recode()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(1, this->recode(), output);
  }

  // required uint32 seq = 2;
  if (has_seq()) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt32(2, this->seq(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* Heartbeat::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required uint32 recode = 1;
  if (has_recode()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(1, this->recode(), target);
  }

  // required uint32 seq = 2;
  if (has_seq()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteUInt32ToArray(2, this->seq(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int Heartbeat::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required uint32 recode = 1;
    if (has_recode()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->recode());
    }

    // required uint32 seq = 2;
    if (has_seq()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::UInt32Size(
          this->seq());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void Heartbeat::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Heartbeat* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Heartbeat*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Heartbeat::MergeFrom(const Heartbeat& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_recode()) {
      set_recode(from.recode());
    }
    if (from.has_seq()) {
      set_seq(from.seq());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Heartbeat::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Heartbeat::CopyFrom(const Heartbeat& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Heartbeat::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;

  return true;
}

void Heartbeat::Swap(Heartbeat* other) {
  if (other != this) {
    std::swap(recode_, other->recode_);
    std::swap(seq_, other->seq_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Heartbeat::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Heartbeat_descriptor_;
  metadata.reflection = Heartbeat_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace generalmess

// @@protoc_insertion_point(global_scope)