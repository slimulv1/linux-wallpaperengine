#include "CProperty.h"
#include "CPropertyBoolean.h"
#include "CPropertyColor.h"
#include "CPropertyCombo.h"
#include "CPropertySlider.h"
#include "CPropertyText.h"
#include "WallpaperEngine/Logging/CLog.h"
#include <iostream>
#include <utility>

using namespace WallpaperEngine::Core::Projects;

std::shared_ptr<CProperty> CProperty::fromJSON (const json& data, const std::string& name) {
    const auto type = jsonFindRequired (data, "type", "Project properties must have the type field");

    if (*type == "color")
        return CPropertyColor::fromJSON (data, name);
    if (*type == "bool")
        return CPropertyBoolean::fromJSON (data, name);
    if (*type == "slider")
        return CPropertySlider::fromJSON (data, name);
    if (*type == "combo")
        return CPropertyCombo::fromJSON (data, name);
    if (*type == "text")
        return CPropertyText::fromJSON (data, name);

    // show the error and ignore this property
    sLog.error ("Unexpected type for property: ", *type);
    sLog.error (data);

    return nullptr;
}

CProperty::CProperty (std::string name, std::string text) :
    m_name (std::move(name)),
    m_text (std::move(text)) {}

void CProperty::subscribe (const function_type& callback) const {
    this->m_subscriptions.push_back (callback);
}

void CProperty::propagate () const {
    CDynamicValue::propagate ();

    for (const auto& callback : this->m_subscriptions) {
        callback(this);
    }
}

const std::string& CProperty::getName () const {
    return this->m_name;
}

const std::string& CProperty::getText () const {
    return this->m_text;
}