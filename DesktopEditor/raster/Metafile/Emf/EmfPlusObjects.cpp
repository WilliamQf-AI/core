﻿#include "EmfPlusObjects.h"

namespace MetaFile
{
	CEmfPlusBrush::CEmfPlusBrush()
		: CEmfPlusObject(), unStyle(BS_SOLID), unHatch(0), unAngle(0)
	{}

	CEmfPlusBrush::~CEmfPlusBrush()
	{
		if (BS_DIBPATTERN == unStyle && !wsDibPatternPath.empty())
			NSFile::CFileBinary::Remove(wsDibPatternPath);
	}

	EEmfObjectType CEmfPlusBrush::GetType() const
	{
		return EMF_OBJECT_BRUSH;
	}

	EEmfPlusObjectType CEmfPlusBrush::GetObjectType() const
	{
		return ObjectTypeBrush;
	}

	int CEmfPlusBrush::GetColor() const
	{
		return METAFILE_RGBA(oColor.chRed, oColor.chGreen, oColor.chBlue, 0);
	}

	int CEmfPlusBrush::GetColor2() const
	{
		return METAFILE_RGBA(oColorBack.chRed, oColorBack.chGreen, oColorBack.chBlue, 0);
	}

	unsigned int CEmfPlusBrush::GetStyle() const
	{
		return unStyle;
	}

	unsigned int CEmfPlusBrush::GetStyleEx() const
	{
		return unAngle;
	}

	unsigned int CEmfPlusBrush::GetHatch() const
	{
		return unHatch;
	}

	unsigned int CEmfPlusBrush::GetAlpha() const
	{
		return oColor.chAlpha;
	}

	unsigned int CEmfPlusBrush::GetAlpha2() const
	{
		return oColorBack.chAlpha;
	}

	std::wstring CEmfPlusBrush::GetDibPatterPath() const
	{
		return wsDibPatternPath;
	}
	
	void CEmfPlusBrush::GetDibPattern(unsigned char **pBuffer, unsigned int &unWidth, unsigned int &unHeight) const
	{}

	void CEmfPlusBrush::GetCenterPoint(double &dX, double &dY) const
	{
		dX = oCenterPoint.X;
		dY = oCenterPoint.Y;
	}

	void CEmfPlusBrush::GetBounds(double &left, double &top, double &width, double &height) const
	{
		left   = oRectF.dX;
		top    = oRectF.dY;
		width  = oRectF.dWidth;
		height = oRectF.dHeight;
	}

	void CEmfPlusBrush::GetGradientColors(std::vector<long>& arColors, std::vector<double>& arPositions) const
	{
		if (arGradientColors.empty())
		{
			arColors    = {(long)(GetColor()  + (GetAlpha()  << 24)), (long)(GetColor2() + (GetAlpha2() << 24))};
			arPositions = {0., 1.};

			return;
		}

		arColors.resize(arGradientColors.size());
		arPositions.resize(arGradientColors.size());

		for (unsigned int unIndex = 0; unIndex < arGradientColors.size(); ++unIndex)
		{
			arColors[unIndex] = METAFILE_RGBA(arGradientColors[unIndex].first.chRed, arGradientColors[unIndex].first.chGreen, arGradientColors[unIndex].first.chBlue, arGradientColors[unIndex].first.chAlpha);
			arPositions[unIndex] = arGradientColors[unIndex].second;
		}
	}

	CEmfPlusPen::CEmfPlusPen()
		: unStyle(PS_SOLID | PS_GEOMETRIC | PS_STARTCAP_FLAT | PS_ENDCAP_FLAT | PS_JOIN_MITER), dWidth(1), oColor(0, 0, 0),
		  pBrush(NULL), dMiterLimit(0), dDashOffset(0),
		  pDataDash(NULL), unSizeDash(0), pLineStartCapData(NULL), pLineEndCapData(NULL) 
	{}

	CEmfPlusPen::~CEmfPlusPen()
	{
		RELEASEOBJECT(pBrush)
		RELEASEARRAYOBJECTS(pDataDash)
		RELEASEOBJECT(pLineStartCapData)
		RELEASEOBJECT(pLineEndCapData)
	}

	EEmfObjectType CEmfPlusPen::GetType() const
	{
		return EMF_OBJECT_PEN;
	}

	EEmfPlusObjectType CEmfPlusPen::GetObjectType() const
	{
		return ObjectTypePen;
	}

	int CEmfPlusPen::GetColor() const
	{
		if (NULL != pBrush)
			return pBrush->GetColor();

		return METAFILE_RGBA(oColor.chRed, oColor.chGreen, oColor.chBlue, 0);
	}

	unsigned int CEmfPlusPen::GetStyle() const
	{
		return unStyle;
	}

	double CEmfPlusPen::GetWidth() const
	{
//		if (dWidth < 0)
//			return 1;

		return dWidth;
	}

	unsigned int CEmfPlusPen::GetAlpha() const
	{
		if (NULL != pBrush)
			return pBrush->oColor.chAlpha;

		return 0xff;
	}

	double CEmfPlusPen::GetMiterLimit() const
	{
		return dMiterLimit;
	}

	double CEmfPlusPen::GetDashOffset() const
	{
		return dDashOffset;
	}

	void CEmfPlusPen::GetDashData(double *&arDatas, unsigned int &unSize) const
	{
		arDatas = pDataDash;
		unSize  = unSizeDash;
	}

	const ILineCap* CEmfPlusPen::GetStartLineCap() const
	{
		return pLineStartCapData;
	}

	const ILineCap* CEmfPlusPen::GetEndLineCap() const
	{
		return pLineEndCapData;
	}

	CEmfPlusFont::CEmfPlusFont()
		: m_dEmSize(18), m_unSizeUnit(0), m_bBold(false),
		  m_bItalic(false), m_bUnderline(false), m_bStrikeout(false),
		  m_wsFamilyName(L"")
	{}

	CEmfPlusFont::~CEmfPlusFont()
	{}

	EEmfObjectType CEmfPlusFont::GetType() const
	{
		return EMF_OBJECT_FONT;
	}

	EEmfPlusObjectType CEmfPlusFont::GetObjectType() const
	{
		return ObjectTypeFont;
	}

	double CEmfPlusFont::GetHeight() const
	{
		return m_dEmSize;
	}

	std::wstring CEmfPlusFont::GetFaceName() const
	{
		return m_wsFamilyName;
	}

	int CEmfPlusFont::GetWeight() const
	{
		return (m_bBold) ? 700 : 400;
	}

	bool CEmfPlusFont::IsItalic() const
	{
		return m_bItalic;
	}

	bool CEmfPlusFont::IsStrikeOut() const
	{
		return m_bStrikeout;
	}

	bool CEmfPlusFont::IsUnderline() const
	{
		return m_bUnderline;
	}

	int CEmfPlusFont::GetEscapement() const
	{
		return 0;
	}

	int CEmfPlusFont::GetCharSet() const
	{
		return 0;
	}

	int CEmfPlusFont::GetOrientation() const
	{
		return 0;
	}

	CEmfPlusBuffer::CEmfPlusBuffer()
		: m_pBuffer(NULL), m_ulPosition(0), m_ulFullSize(0)
	{}

	CEmfPlusBuffer::~CEmfPlusBuffer()
	{
		RELEASEOBJECT(m_pBuffer)
	}

	EEmfPlusObjectType CEmfPlusBuffer::GetObjectType() const
	{
		return ObjectTypeBuffer;
	}

	void CEmfPlusBuffer::SetSize(unsigned int unSize)
	{
		RELEASEOBJECT(m_pBuffer)

		m_pBuffer = new BYTE[unSize];
		m_ulFullSize   = unSize;
	}

	unsigned int CEmfPlusBuffer::GetSize() const
	{
		return m_ulFullSize;
	}

	void CEmfPlusBuffer::AddData(BYTE *pData, unsigned int unSize)
	{
		if (NULL == m_pBuffer && 0 == m_ulFullSize && 0 < unSize)
			SetSize(unSize);
		else if (0 == m_ulFullSize)
			return;

		if (unSize + m_ulPosition > m_ulFullSize)
			unSize = m_ulFullSize - m_ulPosition;

		memcpy(m_pBuffer + m_ulPosition * sizeof (BYTE), pData, unSize);

		m_ulPosition += unSize;
	}

	unsigned int CEmfPlusBuffer::GetUnreadSize() const
	{
		return (m_ulFullSize - m_ulPosition);
	}

	void CEmfPlusBuffer::GetData(BYTE *&pBuffer, unsigned int &unSize) const
	{
		pBuffer = m_pBuffer;
		unSize = m_ulPosition;
	}

	CEmfPlusPath::CEmfPlusPath() : CEmfPlusObject(), CPath()
	{}

	CEmfPlusPath::CEmfPlusPath(CEmfPlusPath *pPath) : CEmfPlusObject(), CPath(*pPath)
	{}

	CEmfPlusPath::~CEmfPlusPath()
	{
		Clear();
	}

	EEmfPlusObjectType CEmfPlusPath::GetObjectType() const
	{
		return ObjectTypePath;
	}

	TRectD CEmfPlusPath::GetBounds() const
	{
		TRectD oRect;
		
		oRect.Right = oRect.Bottom = MININT32;
		oRect.Left  = oRect.Top    = MAXINT32;

		for (const CPathCommandBase* pCommand : GetCommands())
		{
			switch(pCommand->GetType())
			{
			case PATH_COMMAND_MOVETO:
			{
				CPathCommandMoveTo* pMoveTo = (CPathCommandMoveTo*)pCommand;

				oRect.Left   = std::min(oRect.Left,   pMoveTo->GetX());
				oRect.Top    = std::min(oRect.Top,    pMoveTo->GetY());
				oRect.Right  = std::max(oRect.Right,  pMoveTo->GetX());
				oRect.Bottom = std::max(oRect.Bottom, pMoveTo->GetY());

				break;
			}
			case PATH_COMMAND_LINETO:
			{
				CPathCommandLineTo* pLineTo = (CPathCommandLineTo*)pCommand;

				oRect.Left   = std::min(oRect.Left,   pLineTo->GetX());
				oRect.Top    = std::min(oRect.Top,    pLineTo->GetY());
				oRect.Right  = std::max(oRect.Right,  pLineTo->GetX());
				oRect.Bottom = std::max(oRect.Bottom, pLineTo->GetY());

				break;
			}
			case PATH_COMMAND_CURVETO:
			case PATH_COMMAND_ARCTO:
			case PATH_COMMAND_CLOSE:
			case PATH_COMMAND_UNKNOWN:
			break;
			}
		}

		return oRect;
	}

	CEmfPlusImageAttributes::CEmfPlusImageAttributes() : CEmfPlusObject()
	{}
	
	EEmfPlusObjectType CEmfPlusImageAttributes::GetObjectType() const
	{
		return ObjectTypeImageAttributes;
	}

	CEmfPlusImage::CEmfPlusImage()
		: m_eImageDataType(ImageDataTypeUnknown),
		  m_eMetafileDataType(MetafileDataTypeUnknown),
		  m_unWidth(0), m_unHeight(0)
	{}

	EEmfPlusObjectType CEmfPlusImage::GetObjectType() const
	{
		return ObjectTypeImage;
	}

	void CEmfPlusImage::SetImageDataType(unsigned int unImageDataType)
	{
		if (ImageDataTypeBitmap == unImageDataType)
			m_eImageDataType = ImageDataTypeBitmap;
		else if (ImageDataTypeMetafile == unImageDataType)
			m_eImageDataType = ImageDataTypeMetafile;
	}

	EEmfPlusImageDataType CEmfPlusImage::GetImageDataType() const
	{
		return m_eImageDataType;
	}

	bool CEmfPlusImage::SetMetafileType(unsigned int unType)
	{
		switch (unType)
		{
			case 1: m_eMetafileDataType = MetafileDataTypeWmf;              return true;
			case 2: m_eMetafileDataType = MetafileDataTypeWmfPlaceable;     return true;
			case 3: m_eMetafileDataType = MetafileDataTypeEmf;              return true;
			case 4: m_eMetafileDataType = MetafileDataTypeEmfPlusOnly;      return true;
			case 5: m_eMetafileDataType = MetafileDataTypeEmfPlusDual;      return true;
			default:m_eMetafileDataType = MetafileDataTypeUnknown;          return false;
		}
	}

	EEmfPlusMetafileDataType CEmfPlusImage::GetMetafileType() const
	{
		return m_eMetafileDataType;
	}

	void CEmfPlusImage::SetImageSize(unsigned int unWidth, unsigned int unHeight)
	{
		m_unWidth  = unWidth;
		m_unHeight = unHeight;
	}

	void CEmfPlusImage::GetImageSize(unsigned int &unWidth, unsigned int &unHeight)
	{
		unWidth  = m_unWidth;
		unHeight = m_unHeight;
	}

	CEmfPlusRegionNode::CEmfPlusRegionNode()
	{}

	CEmfPlusRegionNode::~CEmfPlusRegionNode()
	{}

	EEmfPlusRegionNodeDataType CEmfPlusRegionNode::GetType() const
	{
		return eType;
	}

	EEmfPLusRegionNodeType CEmfPlusRegionNode::GetNodeType() const
	{
		return EmfPLusRegionNodeTypeEmpty;
	}

	CEmfPlusRegionNodePath::CEmfPlusRegionNodePath() : pPath(NULL)
	{}

	CEmfPlusRegionNodePath::~CEmfPlusRegionNodePath()
	{
		RELEASEOBJECT(pPath);
	}

	EEmfPLusRegionNodeType CEmfPlusRegionNodePath::GetNodeType() const
	{
		return EmfPLusRegionNodeTypePath;
	}

	bool CEmfPlusRegionNodePath::Empty() const
	{
		return (NULL == pPath);
	}

	CEmfPlusPath *CEmfPlusRegionNodePath::GetPath() const
	{
		return pPath;
	}

	CEmfPlusRegionNodeRectF::CEmfPlusRegionNodeRectF() : pRect(NULL)
	{}

	CEmfPlusRegionNodeRectF::~CEmfPlusRegionNodeRectF()
	{
		RELEASEOBJECT(pRect);
	}

	EEmfPLusRegionNodeType CEmfPlusRegionNodeRectF::GetNodeType() const
	{
		return EmfPLusRegionNodeTypeRectF;
	}

	bool CEmfPlusRegionNodeRectF::Empty() const
	{
		return NULL == pRect;
	}

	TEmfPlusRectF *CEmfPlusRegionNodeRectF::GetRect() const
	{
		return pRect;
	}

	CEmfPlusRegionNodeChild::CEmfPlusRegionNodeChild() : pLeft(NULL), pRigth(NULL)
	{}

	CEmfPlusRegionNodeChild::~CEmfPlusRegionNodeChild()
	{
		RELEASEOBJECT(pLeft);
		RELEASEOBJECT(pRigth);
	}

	EEmfPLusRegionNodeType CEmfPlusRegionNodeChild::GetNodeType() const
	{
		return EmfPLusRegionNodeTypeChild;
	}
	
	void CEmfPlusRegionNodeChild::DrawOnClip(CClip &oClip, const TXForm &oTransform, const TRectL *pOutRect)
	{
		unsigned int unType;
		
		switch (eType)
		{
			case RegionNodeDataTypeAnd:
			case RegionNodeDataTypeExclude:
			case RegionNodeDataTypeComplement:
			{
				unType = RGN_AND;
				break;
			}
			case RegionNodeDataTypeOr:
			{
				unType = RGN_OR;
				break;
			}
			case RegionNodeDataTypeXor:
			{
				unType = RGN_XOR;
				break;
			}
			default: return;
		}

		for (CEmfPlusRegionNode *pNode : std::vector<CEmfPlusRegionNode*>{pLeft, pRigth})
		{
			switch (pNode->GetNodeType())
			{
				case EmfPLusRegionNodeTypeEmpty:
				{
					if (NULL != pOutRect)
					{
						CPath oPath;

						oPath.MoveTo(pOutRect->Left,  pOutRect->Top);
						oPath.LineTo(pOutRect->Right, pOutRect->Top);
						oPath.LineTo(pOutRect->Right, pOutRect->Bottom);
						oPath.LineTo(pOutRect->Left,  pOutRect->Bottom);
						oPath.Close();

						oClip.SetPath(oPath, unType, oTransform);
					}
					break;
				}
				case EmfPLusRegionNodeTypePath:
				{
					CEmfPlusRegionNodePath *pRegionNodePath = (CEmfPlusRegionNodePath*)pNode;

					oClip.SetPath(*pRegionNodePath->GetPath(), unType, oTransform);
				}
				case EmfPLusRegionNodeTypeRectF:
				{
					CEmfPlusRegionNodeRectF *pRegionNodeRectF = (CEmfPlusRegionNodeRectF*)pNode;

					if (pRegionNodeRectF->Empty())
						break;
					
					TRectD oRect = pRegionNodeRectF->GetRect()->ToRectD();
					
					CPath oPath;

					oPath.MoveTo(oRect.Left,  oRect.Top);
					oPath.LineTo(oRect.Right, oRect.Top);
					oPath.LineTo(oRect.Right, oRect.Bottom);
					oPath.LineTo(oRect.Left,  oRect.Bottom);
					oPath.Close();

					oClip.SetPath(oPath, unType, oTransform);
				}
				default: break;
			}
		}
	}

	CEmfPlusRegion::CEmfPlusRegion() : CEmfPlusObject()
	{}

	CEmfPlusRegion::~CEmfPlusRegion()
	{
		for (CEmfPlusRegionNode* pNode : arNodes)
			delete pNode;

		arNodes.clear();
	}

	EEmfPlusObjectType CEmfPlusRegion::GetObjectType() const
	{
		return ObjectTypeRegion;
	}

	CEmfPlusStringFormat::CEmfPlusStringFormat() : CEmfPlusObject()
	{}

	EEmfPlusObjectType CEmfPlusStringFormat::GetObjectType() const
	{
		return ObjectTypeStringFormat;
	}
}

namespace MetaFile
{
	TEmfPlusCustomLineCapData::~TEmfPlusCustomLineCapData()
	{
		RELEASEOBJECT(pPath);
	}
}
