//
// Copyright Contributors to the MaterialX Project
// SPDX-License-Identifier: Apache-2.0
//

#include <MaterialXTest/External/Catch/catch.hpp>

#include <MaterialXTest/MaterialXGenGlsl/GenGlsl.h>

#include <MaterialXGenGlsl/EsslShaderGenerator.h>
#include <MaterialXGenGlsl/EsslSyntax.h>
#include <MaterialXGenGlsl/GlslShaderGenerator.h>
#include <MaterialXGenGlsl/GlslSyntax.h>
#include <MaterialXGenGlsl/GlslResourceBindingContext.h>
#include <MaterialXGenGlsl/VkShaderGenerator.h>
#include <MaterialXGenGlsl/WgslShaderGenerator.h>

namespace mx = MaterialX;

TEST_CASE("GenShader: GLSL Syntax Check", "[genglsl]")
{
    mx::TypeSystemPtr ts = mx::TypeSystem::create();
    mx::SyntaxPtr syntax = mx::GlslSyntax::create(ts);

    REQUIRE(syntax->getTypeName(mx::Type::FLOAT) == "float");
    REQUIRE(syntax->getTypeName(mx::Type::COLOR3) == "vec3");
    REQUIRE(syntax->getTypeName(mx::Type::VECTOR3) == "vec3");

    REQUIRE(syntax->getTypeName(mx::Type::BSDF) == "BSDF");
    REQUIRE(syntax->getOutputTypeName(mx::Type::BSDF) == "out BSDF");

    // Set fixed precision with one digit
    mx::ScopedFloatFormatting format(mx::Value::FloatFormatFixed, 1);

    std::string value;
    value = syntax->getDefaultValue(mx::Type::FLOAT);
    REQUIRE(value == "0.0");
    value = syntax->getDefaultValue(mx::Type::COLOR3);
    REQUIRE(value == "vec3(0.0)");
    value = syntax->getDefaultValue(mx::Type::COLOR3, true);
    REQUIRE(value == "vec3(0.0)");
    value = syntax->getDefaultValue(mx::Type::COLOR4);
    REQUIRE(value == "vec4(0.0)");
    value = syntax->getDefaultValue(mx::Type::COLOR4, true);
    REQUIRE(value == "vec4(0.0)");
    value = syntax->getDefaultValue(mx::Type::FLOATARRAY, true);
    REQUIRE(value.empty());
    value = syntax->getDefaultValue(mx::Type::INTEGERARRAY, true);
    REQUIRE(value.empty());

    mx::ValuePtr floatValue = mx::Value::createValue<float>(42.0f);
    value = syntax->getValue(mx::Type::FLOAT, *floatValue);
    REQUIRE(value == "42.0");
    value = syntax->getValue(mx::Type::FLOAT, *floatValue, true);
    REQUIRE(value == "42.0");

    mx::ValuePtr color3Value = mx::Value::createValue<mx::Color3>(mx::Color3(1.0f, 2.0f, 3.0f));
    value = syntax->getValue(mx::Type::COLOR3, *color3Value);
    REQUIRE(value == "vec3(1.0, 2.0, 3.0)");
    value = syntax->getValue(mx::Type::COLOR3, *color3Value, true);
    REQUIRE(value == "vec3(1.0, 2.0, 3.0)");

    mx::ValuePtr color4Value = mx::Value::createValue<mx::Color4>(mx::Color4(1.0f, 2.0f, 3.0f, 4.0f));
    value = syntax->getValue(mx::Type::COLOR4, *color4Value);
    REQUIRE(value == "vec4(1.0, 2.0, 3.0, 4.0)");
    value = syntax->getValue(mx::Type::COLOR4, *color4Value, true);
    REQUIRE(value == "vec4(1.0, 2.0, 3.0, 4.0)");

    std::vector<float> floatArray = { 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f };
    mx::ValuePtr floatArrayValue = mx::Value::createValue<std::vector<float>>(floatArray);
    value = syntax->getValue(mx::Type::FLOATARRAY, *floatArrayValue);
    REQUIRE(value == "float[7](0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7)");

    std::vector<int> intArray = { 1, 2, 3, 4, 5, 6, 7 };
    mx::ValuePtr intArrayValue = mx::Value::createValue<std::vector<int>>(intArray);
    value = syntax->getValue(mx::Type::INTEGERARRAY, *intArrayValue);
    REQUIRE(value == "int[7](1, 2, 3, 4, 5, 6, 7)");
}

TEST_CASE("GenShader: GLSL Implementation Check", "[genglsl]")
{
    mx::GenContext context(mx::GlslShaderGenerator::create());

    mx::StringSet generatorSkipNodeTypes;
    mx::StringSet generatorSkipNodeDefs;
    GenShaderUtil::checkImplementations(context, generatorSkipNodeTypes, generatorSkipNodeDefs);
}

TEST_CASE("GenShader: GLSL Unique Names", "[genglsl]")
{
    mx::GenContext context(mx::GlslShaderGenerator::create());
    context.registerSourceCodeSearchPath(mx::getDefaultDataSearchPath());
    GenShaderUtil::testUniqueNames(context, mx::Stage::PIXEL);
}

TEST_CASE("GenShader: GLSL Light Shaders", "[genglsl]")
{
    mx::DocumentPtr doc = mx::createDocument();

    mx::FileSearchPath searchPath = mx::getDefaultDataSearchPath();
    loadLibraries({ "libraries" }, searchPath, doc);

    mx::NodeDefPtr pointLightShader = doc->getNodeDef("ND_point_light");
    mx::NodeDefPtr spotLightShader = doc->getNodeDef("ND_spot_light");
    REQUIRE(pointLightShader != nullptr);
    REQUIRE(spotLightShader != nullptr);

    mx::GenContext context(mx::GlslShaderGenerator::create());
    context.registerSourceCodeSearchPath(searchPath);
    context.getShaderGenerator().registerTypeDefs(doc);

    mx::HwShaderGenerator::bindLightShader(*pointLightShader, 42, context);
    REQUIRE_THROWS(mx::HwShaderGenerator::bindLightShader(*spotLightShader, 42, context));
    mx::HwShaderGenerator::unbindLightShader(42, context);
    REQUIRE_NOTHROW(mx::HwShaderGenerator::bindLightShader(*spotLightShader, 42, context));
    REQUIRE_NOTHROW(mx::HwShaderGenerator::bindLightShader(*pointLightShader, 66, context));
    mx::HwShaderGenerator::unbindLightShaders(context);
    REQUIRE_NOTHROW(mx::HwShaderGenerator::bindLightShader(*spotLightShader, 66, context));
}

#ifdef MATERIALX_BUILD_BENCHMARK_TESTS
TEST_CASE("GenShader: GLSL Performance Test", "[genglsl]")
{
    mx::GenContext context(mx::GlslShaderGenerator::create());
    BENCHMARK("Load documents, validate and generate shader") 
    {
        return GenShaderUtil::shaderGenPerformanceTest(context);
    };
}
#endif

enum class GlslType
{
    Essl,
    Glsl,
    GlslLayout,
    GlslVulkan,
    GlslWgsl
};

static void generateGlslCode(GlslType type)
{
    mx::FileSearchPath searchPath = mx::getDefaultDataSearchPath();

    mx::FilePathVec testRootPaths;
    testRootPaths.push_back(searchPath.find("resources/Materials/TestSuite"));
    testRootPaths.push_back(searchPath.find("resources/Materials/Examples/StandardSurface"));

    // Create the requested shader generator.
    mx::ShaderGeneratorPtr generator;
    if (type == GlslType::Essl)
    {
        generator = mx::EsslShaderGenerator::create();
    }
    else if (type == GlslType::GlslVulkan)
    {
        generator = mx::VkShaderGenerator::create();
    }
    else if (type == GlslType::GlslWgsl)
    {
        generator = mx::WgslShaderGenerator::create();
    }
    else
    {
        generator = mx::GlslShaderGenerator::create();
    }

    const std::unordered_map<GlslType, std::string> TYPE_NAME_MAP =
    {
        { GlslType::Essl, "essl" },
        { GlslType::Glsl, "glsl" },
        { GlslType::GlslLayout, "glsl_layout" },
        { GlslType::GlslVulkan, "glsl_vulkan" },
        { GlslType::GlslWgsl  , "glsl_wgsl" }
    };
    const mx::FilePath logPath("genglsl_" + TYPE_NAME_MAP.at(type) + "_generate_test.txt");
    GlslShaderGeneratorTester tester(generator, testRootPaths, searchPath, logPath, false);

    // Handle resource binding layouts if requested.
    if (type == GlslType::GlslLayout)
    {
        mx::GlslResourceBindingContextPtr glslresourceBinding(mx::GlslResourceBindingContext::create());
        glslresourceBinding->enableSeparateBindingLocations(true);
        tester.addUserData(mx::HW::USER_DATA_BINDING_CONTEXT, glslresourceBinding);
    }

    const mx::GenOptions genOptions;
    mx::FilePath optionsFilePath = searchPath.find("resources/Materials/TestSuite/_options.mtlx");
    tester.validate(genOptions, optionsFilePath);
}

TEST_CASE("GenShader: ESSL Shader Generation", "[genglsl]")
{
    generateGlslCode(GlslType::Essl);
}

TEST_CASE("GenShader: GLSL Shader Generation", "[genglsl]")
{
    generateGlslCode(GlslType::Glsl);
}

TEST_CASE("GenShader: GLSL Shader Generation with Layout", "[genglsl]")
{
    generateGlslCode(GlslType::GlslLayout);
}

TEST_CASE("GenShader: Vulkan GLSL Shader Generation", "[genglsl]")
{
    generateGlslCode(GlslType::GlslVulkan);
}

TEST_CASE("GenShader: Wgsl GLSL Shader Generation", "[genglsl]")
{
    generateGlslCode(GlslType::GlslWgsl);
}
