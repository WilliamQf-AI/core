﻿/*
 * (c) Copyright Ascensio System SIA 2010-2023
 *
 * This program is a free software product. You can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License (AGPL)
 * version 3 as published by the Free Software Foundation. In accordance with
 * Section 7(a) of the GNU AGPL its Section 15 shall be amended to the effect
 * that Ascensio System SIA expressly excludes the warranty of non-infringement
 * of any third-party rights.
 *
 * This program is distributed WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR  PURPOSE. For
 * details, see the GNU AGPL at: http://www.gnu.org/licenses/agpl-3.0.html
 *
 * You can contact Ascensio System SIA at 20A-6 Ernesta Birznieka-Upish
 * street, Riga, Latvia, EU, LV-1050.
 *
 * The  interactive user interfaces in modified source and object code versions
 * of the Program must display Appropriate Legal Notices, as required under
 * Section 5 of the GNU AGPL version 3.
 *
 * Pursuant to Section 7(b) of the License you must retain the original Product
 * logo when distributing the program. Pursuant to Section 7(e) we decline to
 * grant you any rights under trademark law for use of our trademarks.
 *
 * All the Product's GUI elements, including illustrations and icon sets, as
 * well as technical writing content are licensed under the terms of the
 * Creative Commons Attribution-ShareAlike 4.0 International. See the License
 * terms at http://creativecommons.org/licenses/by-sa/4.0/legalcode
 *
 */
#pragma once

#include "Folder.h"
#include "Presentation.h"
#include "Slide.h"
#include "SlideLayout.h"
#include "SlideMaster.h"
#include "NotesMaster.h"
#include "ViewProps.h"
#include "PresProps.h"
#include "TableStyles.h"

#include "Logic/Bg.h"
#include "Logic/Shape.h"
#include "Logic/Pic.h"
#include "Logic/CxnSp.h"
#include "Logic/GraphicFrame.h"
#include "Logic/TxBody.h"
#include "Logic/SpTree.h"
#include "Logic/UniFill.h"
#include "Logic/UniColor.h"
#include "Logic/Ln.h"
#include "Logic/LineJoin.h"
#include "Logic/Transitions/Transition.h"
#include "Logic/Timing/Timing.h"
#include "Logic/Timing/TnLst.h"
#include "Logic/Timing/TimeNodeBase.h"
#include "Logic/Timing/CTn.h"
#include "Logic/Timing/CBhvr.h"
#include "Logic/Timing/CondLst.h"
#include "Logic/Table/Table.h"
#include "Logic/TableStyle.h"
#include "Logic/Runs/Run.h"
#include "Logic/Runs/Fld.h"
#include "Logic/Runs/Br.h"
#include "Logic/XmlId.h"

#include "../DocxFormat/CustomXml.h"
#include "../DocxFormat/App.h"
#include "../DocxFormat/Core.h"