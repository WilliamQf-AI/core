#pragma once

#include <iosfwd>
#include <cpdoccore/CPOptional.h>
#include <cpdoccore/xml/xmlelement.h>
#include <cpdoccore/xml/nodetype.h>
#include "office_elements.h"
#include "office_elements_create.h"
#include "common_attlists.h"

namespace cpdoccore { 
namespace odf {

class draw_base : public office_element_impl<draw_base>
{
public:
    static const wchar_t * ns;
    static const wchar_t * name;
    static const xml::NodeType xml_type = xml::typeElement;
    static const ElementType type = typeDrawBase;
    
	CPDOCCORE_DEFINE_VISITABLE();

	virtual void create_child_element(const ::std::wstring & Ns, const ::std::wstring & Name);
    virtual void add_child_element( office_element_ptr & child_element);

    virtual void serialize(std::wostream & _Wostream);
    virtual void serialize_attlist(CP_ATTR_NODE);

	common_presentation_attlist common_presentation_attlist_;
	union_common_draw_attlists  common_draw_attlists_;

    office_element_ptr_array content_;

};

}
}