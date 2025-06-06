#pragma once

#include "WallpaperEngine/Core/Objects/Particles/CControlPoint.h"
#include "WallpaperEngine/Core/Objects/Particles/CEmitter.h"
#include "WallpaperEngine/Core/Objects/Particles/CInitializer.h"

#include "WallpaperEngine/Core/CObject.h"
#include "WallpaperEngine/Core/Core.h"

namespace WallpaperEngine::Core::Objects {
using json = nlohmann::json;

/**
 * Represents a particle system in the background
 */
class CParticle : public CObject {
    friend class CObject;

  public:
    static const CParticle* fromFile (
        std::shared_ptr <const Core::CProject> project, const std::string& filename,
        const std::shared_ptr<const CContainer>& container, const CUserSettingBoolean* visible, int id,
        const std::string& name, const CUserSettingVector3* origin, const CUserSettingVector3* angles,
        const CUserSettingVector3* scale, std::vector<int> dependencies);

    /**
     * @return The list of emitters for the particle system
     */
    [[nodiscard]] const std::vector<const Particles::CEmitter*>& getEmitters () const;
    /**
     * @return The list of control points for the particle system
     */
    [[nodiscard]] const std::vector<const Particles::CControlPoint*>& getControlPoints () const;
    /**
     * @return The list of initializers for the particle system
     */
    [[nodiscard]] const std::vector<const Particles::CInitializer*>& getInitializers () const;

  protected:
    CParticle (
        std::shared_ptr <const Core::CProject> project, uint32_t starttime, uint32_t maxcount,
        const CUserSettingBoolean* visible, int id, const std::string& name, const CUserSettingVector3* origin,
        const CUserSettingVector3* scale, const CUserSettingVector3* angles,
        const std::vector<const Particles::CControlPoint*>& controlpoints,
        const std::vector<const Particles::CEmitter*>& emitters,
        const std::vector<const Particles::CInitializer*>& initializers, std::vector<int> dependencies);

  private:
    /** The time at which the particle system should start emitting */
    const uint32_t m_starttime;
    /** Maximum number of particles at the same time */
    const uint32_t m_maxcount;
    /** List of control points */
    const std::vector<const Particles::CControlPoint*> m_controlpoints;
    /** List of emitters */
    const std::vector<const Particles::CEmitter*> m_emitters;
    /** List of initializers */
    const std::vector<const Particles::CInitializer*> m_initializers;
};
} // namespace WallpaperEngine::Core::Objects
