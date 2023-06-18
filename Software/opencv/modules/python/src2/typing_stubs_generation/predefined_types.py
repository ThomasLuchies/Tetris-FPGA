from .nodes.type_node import (
    AliasTypeNode, AliasRefTypeNode, PrimitiveTypeNode,
    ASTNodeTypeNode, NDArrayTypeNode, NoneTypeNode, SequenceTypeNode,
    TupleTypeNode, UnionTypeNode, AnyTypeNode
)

# Set of predefined types used to cover cases when library doesn't
# directly exports a type and equivalent one should be used instead.
# Example: Instead of C++ `cv::Rect(1, 1, 5, 6)` in Python any sequence type
# with length 4 can be used: tuple `(1, 1, 5, 6)` or list `[1, 1, 5, 6]`.
# Predefined type might be:
#   - alias - defines a Python synonym for a native type name.
#     Example: `cv::Rect` and `cv::Size` are both `Sequence[int]` in Python, but
#     with different length constraints (4 and 2 accordingly).
#   - direct substitution - just a plain type replacement without any credits to
#     native type. Example:
#       * `std::vector<uchar>` is `np.ndarray` with `dtype == np.uint8` in Python
#       * `double` is a Python `float`
#       * `std::string` is a Python `str`
_PREDEFINED_TYPES = (
    PrimitiveTypeNode.int_("int"),
    PrimitiveTypeNode.int_("uchar"),
    PrimitiveTypeNode.int_("unsigned"),
    PrimitiveTypeNode.int_("int64"),
    PrimitiveTypeNode.int_("size_t"),
    PrimitiveTypeNode.float_("float"),
    PrimitiveTypeNode.float_("double"),
    PrimitiveTypeNode.bool_("bool"),
    PrimitiveTypeNode.str_("string"),
    PrimitiveTypeNode.str_("char"),
    PrimitiveTypeNode.str_("String"),
    PrimitiveTypeNode.str_("c_string"),
    NoneTypeNode("void"),
    AliasTypeNode.int_("void*", "IntPointer", "Represents an arbitrary pointer"),
    AliasTypeNode.union_(
        "Mat",
        items=(ASTNodeTypeNode("Mat", module_name="cv2.mat_wrapper"),
               NDArrayTypeNode("Mat")),
        export_name="MatLike"
    ),
    AliasTypeNode.sequence_("MatShape", PrimitiveTypeNode.int_()),
    AliasTypeNode.sequence_("Size", PrimitiveTypeNode.int_(),
                            comment="Required length is 2"),
    AliasTypeNode.sequence_("Size2f", PrimitiveTypeNode.float_(),
                            comment="Required length is 2"),
    AliasTypeNode.sequence_("Scalar", PrimitiveTypeNode.float_(),
                            comment="Required length is at most 4"),
    AliasTypeNode.sequence_("Point", PrimitiveTypeNode.int_(),
                            comment="Required length is 2"),
    AliasTypeNode.ref_("Point2i", "Point"),
    AliasTypeNode.sequence_("Point2f", PrimitiveTypeNode.float_(),
                            comment="Required length is 2"),
    AliasTypeNode.sequence_("Point2d", PrimitiveTypeNode.float_(),
                            comment="Required length is 2"),
    AliasTypeNode.sequence_("Point3i", PrimitiveTypeNode.int_(),
                            comment="Required length is 3"),
    AliasTypeNode.sequence_("Point3f", PrimitiveTypeNode.float_(),
                            comment="Required length is 3"),
    AliasTypeNode.sequence_("Point3d", PrimitiveTypeNode.float_(),
                            comment="Required length is 3"),
    AliasTypeNode.sequence_("Range", PrimitiveTypeNode.int_(),
                            comment="Required length is 2"),
    AliasTypeNode.sequence_("Rect", PrimitiveTypeNode.int_(),
                            comment="Required length is 4"),
    AliasTypeNode.sequence_("Rect2i", PrimitiveTypeNode.int_(),
                            comment="Required length is 4"),
    AliasTypeNode.sequence_("Rect2d", PrimitiveTypeNode.float_(),
                            comment="Required length is 4"),
    AliasTypeNode.dict_("Moments", PrimitiveTypeNode.str_("Moments::key"),
                        PrimitiveTypeNode.float_("Moments::value")),
    AliasTypeNode.tuple_("RotatedRect",
                         items=(AliasRefTypeNode("Point2f"),
                                AliasRefTypeNode("Size"),
                                PrimitiveTypeNode.float_()),
                         comment="Any type providing sequence protocol is supported"),
    AliasTypeNode.tuple_("TermCriteria",
                         items=(
                             ASTNodeTypeNode("TermCriteria.Type"),
                             PrimitiveTypeNode.int_(),
                             PrimitiveTypeNode.float_()),
                         comment="Any type providing sequence protocol is supported"),
    AliasTypeNode.sequence_("Vec2i", PrimitiveTypeNode.int_(),
                            comment="Required length is 2"),
    AliasTypeNode.sequence_("Vec2f", PrimitiveTypeNode.float_(),
                            comment="Required length is 2"),
    AliasTypeNode.sequence_("Vec2d", PrimitiveTypeNode.float_(),
                            comment="Required length is 2"),
    AliasTypeNode.sequence_("Vec3i", PrimitiveTypeNode.int_(),
                            comment="Required length is 3"),
    AliasTypeNode.sequence_("Vec3f", PrimitiveTypeNode.float_(),
                            comment="Required length is 3"),
    AliasTypeNode.sequence_("Vec3d", PrimitiveTypeNode.float_(),
                            comment="Required length is 3"),
    AliasTypeNode.sequence_("Vec4i", PrimitiveTypeNode.int_(),
                            comment="Required length is 4"),
    AliasTypeNode.sequence_("Vec4f", PrimitiveTypeNode.float_(),
                            comment="Required length is 4"),
    AliasTypeNode.sequence_("Vec4d", PrimitiveTypeNode.float_(),
                            comment="Required length is 4"),
    AliasTypeNode.sequence_("Vec6f", PrimitiveTypeNode.float_(),
                            comment="Required length is 6"),
    AliasTypeNode.class_("FeatureDetector", "Feature2D",
                         export_name="FeatureDetector"),
    AliasTypeNode.class_("DescriptorExtractor", "Feature2D",
                         export_name="DescriptorExtractor"),
    AliasTypeNode.class_("FeatureExtractor", "Feature2D",
                         export_name="FeatureExtractor"),
    AliasTypeNode.union_("GProtoArg",
                         items=(AliasRefTypeNode("Scalar"),
                                ASTNodeTypeNode("GMat"),
                                ASTNodeTypeNode("GOpaqueT"),
                                ASTNodeTypeNode("GArrayT"))),
    SequenceTypeNode("GProtoArgs", AliasRefTypeNode("GProtoArg")),
    AliasTypeNode.sequence_("GProtoInputArgs", AliasRefTypeNode("GProtoArg")),
    AliasTypeNode.sequence_("GProtoOutputArgs", AliasRefTypeNode("GProtoArg")),
    AliasTypeNode.union_(
        "GRunArg",
        items=(AliasRefTypeNode("Mat", "MatLike"),
               AliasRefTypeNode("Scalar"),
               ASTNodeTypeNode("GOpaqueT"),
               ASTNodeTypeNode("GArrayT"),
               SequenceTypeNode("GRunArg", AnyTypeNode("GRunArg")),
               NoneTypeNode("GRunArg"))
    ),
    AliasTypeNode.optional_("GOptRunArg", AliasRefTypeNode("GRunArg")),
    AliasTypeNode.union_("GMetaArg",
                         items=(ASTNodeTypeNode("GMat"),
                                AliasRefTypeNode("Scalar"),
                                ASTNodeTypeNode("GOpaqueT"),
                                ASTNodeTypeNode("GArrayT"))),
    AliasTypeNode.union_("Prim",
                         items=(ASTNodeTypeNode("gapi.wip.draw.Text"),
                                ASTNodeTypeNode("gapi.wip.draw.Circle"),
                                ASTNodeTypeNode("gapi.wip.draw.Image"),
                                ASTNodeTypeNode("gapi.wip.draw.Line"),
                                ASTNodeTypeNode("gapi.wip.draw.Rect"),
                                ASTNodeTypeNode("gapi.wip.draw.Mosaic"),
                                ASTNodeTypeNode("gapi.wip.draw.Poly"))),
    SequenceTypeNode("Prims", AliasRefTypeNode("Prim")),
    AliasTypeNode.array_("Matx33f", (3, 3), "numpy.float32"),
    AliasTypeNode.array_("Matx33d", (3, 3), "numpy.float64"),
    AliasTypeNode.array_("Matx44f", (4, 4), "numpy.float32"),
    AliasTypeNode.array_("Matx44d", (4, 4), "numpy.float64"),
    NDArrayTypeNode("vector<uchar>", dtype="numpy.uint8"),
    NDArrayTypeNode("vector_uchar", dtype="numpy.uint8"),
    TupleTypeNode("GMat2", items=(ASTNodeTypeNode("GMat"),
                                  ASTNodeTypeNode("GMat"))),
    ASTNodeTypeNode("GOpaque", "GOpaqueT"),
    ASTNodeTypeNode("GArray", "GArrayT"),
    AliasTypeNode.union_("GTypeInfo",
                         items=(ASTNodeTypeNode("GMat"),
                                AliasRefTypeNode("Scalar"),
                                ASTNodeTypeNode("GOpaqueT"),
                                ASTNodeTypeNode("GArrayT"))),
    SequenceTypeNode("GCompileArgs", ASTNodeTypeNode("GCompileArg")),
    SequenceTypeNode("GTypesInfo", AliasRefTypeNode("GTypeInfo")),
    SequenceTypeNode("GRunArgs", AliasRefTypeNode("GRunArg")),
    SequenceTypeNode("GMetaArgs", AliasRefTypeNode("GMetaArg")),
    SequenceTypeNode("GOptRunArgs", AliasRefTypeNode("GOptRunArg")),
    AliasTypeNode.callable_(
        "detail_ExtractArgsCallback",
        arg_types=SequenceTypeNode("GTypesInfo", AliasRefTypeNode("GTypeInfo")),
        ret_type=SequenceTypeNode("GRunArgs", AliasRefTypeNode("GRunArg")),
        export_name="ExtractArgsCallback"
    ),
    AliasTypeNode.callable_(
        "detail_ExtractMetaCallback",
        arg_types=SequenceTypeNode("GTypesInfo", AliasRefTypeNode("GTypeInfo")),
        ret_type=SequenceTypeNode("GMetaArgs", AliasRefTypeNode("GMetaArg")),
        export_name="ExtractMetaCallback"
    ),
    AliasTypeNode.class_("LayerId", "DictValue"),
    PrimitiveTypeNode.int_("cvflann_flann_distance_t"),
    PrimitiveTypeNode.int_("flann_flann_distance_t"),
    PrimitiveTypeNode.int_("cvflann_flann_algorithm_t"),
    PrimitiveTypeNode.int_("flann_flann_algorithm_t"),
    AliasTypeNode.dict_("flann_IndexParams",
                        key_type=PrimitiveTypeNode.str_(),
                        value_type=UnionTypeNode("flann_IndexParams::value", items=(
                            PrimitiveTypeNode.bool_(),
                            PrimitiveTypeNode.int_(),
                            PrimitiveTypeNode.float_(),
                            PrimitiveTypeNode.str_())
                        ), export_name="IndexParams"),
    AliasTypeNode.dict_("flann_SearchParams",
                        key_type=PrimitiveTypeNode.str_(),
                        value_type=UnionTypeNode("flann_IndexParams::value", items=(
                            PrimitiveTypeNode.bool_(),
                            PrimitiveTypeNode.int_(),
                            PrimitiveTypeNode.float_(),
                            PrimitiveTypeNode.str_())
                        ), export_name="SearchParams"),
    AliasTypeNode.dict_("map_string_and_string", PrimitiveTypeNode.str_("map_string_and_string::key"),
                        PrimitiveTypeNode.str_("map_string_and_string::key::value")),
    AliasTypeNode.dict_("map_string_and_int", PrimitiveTypeNode.str_("map_string_and_int::key"),
                        PrimitiveTypeNode.int_("map_string_and_int::key::value")),
    AliasTypeNode.dict_("map_string_and_vector_size_t", PrimitiveTypeNode.str_("map_string_and_vector_size_t::key"),
                        SequenceTypeNode("map_string_and_vector_size_t::key::value", PrimitiveTypeNode.int_("size_t"))),
    AliasTypeNode.dict_("map_string_and_vector_float", PrimitiveTypeNode.str_("map_string_and_vector_float::key"),
                        SequenceTypeNode("map_string_and_vector_float::key::value", PrimitiveTypeNode.float_())),
)

PREDEFINED_TYPES = dict(zip((t.ctype_name for t in _PREDEFINED_TYPES), _PREDEFINED_TYPES))
