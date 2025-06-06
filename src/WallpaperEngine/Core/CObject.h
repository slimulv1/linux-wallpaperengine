#pragma once

#include "Core.h"

#include "WallpaperEngine/Assets/CContainer.h"
#include "WallpaperEngine/Core/Objects/CEffect.h"
#include "WallpaperEngine/Core/UserSettings/CUserSettingBoolean.h"
#include "WallpaperEngine/Core/UserSettings/CUserSettingFloat.h"
#include "WallpaperEngine/Core/UserSettings/CUserSettingVector3.h"

namespace WallpaperEngine::Core::Wallpapers {
class CScene;
}

namespace WallpaperEngine::Core::Objects {
class CEffect;
}

namespace WallpaperEngine::Core::UserSettings {
class CUserSettingBoolean;
}

namespace WallpaperEngine::Core {
using json = nlohmann::json;
using namespace WallpaperEngine::Assets;
using namespace WallpaperEngine::Core::UserSettings;

class CObject {
    friend class Wallpapers::CScene;

  public:
    static const CObject* fromJSON ( const json& data, std::shared_ptr <const Core::CProject> project,
        const std::shared_ptr<const CContainer>& container);

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

    [[nodiscard]] const std::vector<int>& getDependencies () const;
    [[nodiscard]] int getId () const;

    [[nodiscard]] const glm::vec3& getOrigin () const;
    [[nodiscard]] const glm::vec3& getScale () const;
    [[nodiscard]] const glm::vec3& getAngles () const;
    [[nodiscard]] const std::string& getName () const;

    [[nodiscard]] bool isVisible () const;
    [[nodiscard]] std::shared_ptr <const Core::CProject> getProject () const;

  protected:
    CObject (
        std::shared_ptr <const Core::CProject> scene, const CUserSettingBoolean* visible, int id, std::string name,
        const CUserSettingVector3* origin, const CUserSettingVector3* scale, const CUserSettingVector3* angles,
        std::vector<int> dependencies);

    virtual ~CObject () = default;

  private:
    const CUserSettingBoolean* m_visible;
    int m_id = 0;
    const std::string m_name;
    const CUserSettingVector3* m_origin;
    const CUserSettingVector3* m_scale;
    const CUserSettingVector3* m_angles;

    const std::vector<int> m_dependencies;

    const std::shared_ptr <const Core::CProject> m_project;
};
} // namespace WallpaperEngine::Core
