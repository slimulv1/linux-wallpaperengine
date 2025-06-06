#pragma once

#include <string>

#include "WallpaperEngine/Core/CObject.h"
#include "WallpaperEngine/Render/Helpers/CContextAware.h"

#include "WallpaperEngine/Render/Wallpapers/CScene.h"

namespace WallpaperEngine::Render::Wallpapers {
class CScene;
}

namespace WallpaperEngine::Render {
class CObject : public Helpers::CContextAware {
  public:
    template <class T> [[nodiscard]] const T* as () const {
        if (is <T> ()) {
            return static_cast <const T*> (this);
        }

        throw std::bad_cast ();
    }

    template <class T> [[nodiscard]] T* as () {
        if (is <T> ()) {
            return static_cast <T*> (this);
        }

        throw std::bad_cast ();
    }

    template <class T> [[nodiscard]] bool is () const {
        return typeid (*this) == typeid(T);
    }

    virtual void render () = 0;

    [[nodiscard]] Wallpapers::CScene* getScene () const;
    [[nodiscard]] std::shared_ptr<const CContainer> getContainer () const;
    [[nodiscard]] int getId () const;

  protected:
    CObject (Wallpapers::CScene* scene, const Core::CObject* object);
    virtual ~CObject () override = default;

  private:
    Wallpapers::CScene* m_scene = nullptr;
    const Core::CObject* m_object;
};
} // namespace WallpaperEngine::Render