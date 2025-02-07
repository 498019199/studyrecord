#pragma once

#include <core/SceneNode.h>

class LightSource: public SceneNode
{
public:
    // 光照模型
    enum LightType
    {
        LT_Ambient = 0,
        LT_Directional,     //平行光
        LT_Point,           //点光
        LT_Spot,            // 聚光灯
        LT_SphereArea,
        LT_TubeArea,

        LT_NumLightTypes
    };

    enum LightSrcAttrib
    {
        LSA_NoShadow = 1UL << 0,
        LSA_NoDiffuse = 1UL << 1,
        LSA_NoSpecular = 1UL << 2,
        LSA_IndirectLighting = 1UL << 3,
        LSA_Temporary = 1UL << 4
    };
public:
	explicit LightSource(LightType type);
	virtual ~LightSource() noexcept;

	LightType Type() const;

    const float3& Position() const;
    const float3& Direction() const;
    quater Rotation() const;

    virtual const float3& Falloff() const;
	virtual void Falloff(float3 const & fall_off);

    virtual float Range() const;
	virtual void Range(float range);
private:
    LightType type_;
    float4 color_ = float4(0, 0, 0, 0); // 光源颜色
    float range_ = -1; // 光照范围
    float3 falloff_; // 衰退系数
};

class AmbientLightSource: public LightSource
{

};

class DirectionalLightSource: public LightSource
{

};

class PointLightSource: public LightSource
{

};

class SpotLightSource: public LightSource
{

};

class SphereAreaLightSource: public LightSource
{

};

class TubeAreaLightSource: public LightSource
{

};