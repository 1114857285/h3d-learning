#pragma once
#include "Graphics.h"
#include <DirectXMath.h>
#include <memory>
#include <random>

class Bindable;

class Drawable
{
	template<class T>
	friend class DrawableBase;
public:
	Drawable() = default;
	Drawable(const Drawable&) = delete;
	virtual DirectX::XMMATRIX GetTransformXM() const noexcept = 0;
	void Draw(Graphics& gfx) const noexcept(NDEBUG);
	virtual void Update(float dt) noexcept = 0;
	virtual ~Drawable() = default;
protected:
	template<class T>
	T* QueryBindable() noexcept
	{
		for (auto& pb : binds)
		{
			if (auto pt = dynamic_cast<T*>(pb.get()))
			{
				return pt;
			}
		}
		return nullptr;
	}
	void AddBind(std::unique_ptr<Bindable> bind)noexcept(NDEBUG);
	void AddIndexBuffer(std::unique_ptr<class IndexBuffer> ibuf)noexcept;
private:
	virtual const std::vector<std::unique_ptr<Bindable>>& GetStaticBinds() const noexcept = 0;
private:
	const class IndexBuffer* pIndexBuffer = nullptr;
	std::vector<std::unique_ptr<Bindable>> binds;
};