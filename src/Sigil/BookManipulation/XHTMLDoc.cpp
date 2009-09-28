/************************************************************************
**
**  Copyright (C) 2009  Strahinja Markovic
**
**  This file is part of Sigil.
**
**  Sigil is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  Sigil is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with Sigil.  If not, see <http://www.gnu.org/licenses/>.
**
*************************************************************************/

#include <stdafx.h>
#include "../BookManipulation/XHTMLDoc.h"
#include <QDomDocument>

static const QString HEAD_ELEMENT = "<\\s*(?:head|HEAD)[^>]*>(.*)</\\s*(?:head|HEAD)[^>]*>";


// Returns a list of QDomNodes representing all
// the elements of the specified tag name
// in the head section of the provided XHTML source code
QList< QDomNode > XHTMLDoc::GetTagsInHead( const QString &source, const QString &tag_name )
{
    QRegExp head_element( HEAD_ELEMENT );

    source.contains( head_element );

    QDomDocument document;
    document.setContent( head_element.cap( 0 ) );
   
    return DeepCopyNodeList( document.elementsByTagName( tag_name ) );
}


// Returns a list of QDomNodes representing all
// the elements of the specified tag name
// in the entire document of the provided XHTML source code
QList< QDomNode > XHTMLDoc::GetTagsInDocument( const QString &source, const QString &tag_name )
{
    QDomDocument document;
    document.setContent( source );

    return DeepCopyNodeList( document.elementsByTagName( tag_name ) );
}


// Returns a list of deeply copied QDomNodes
// from the specified QDomNodeList
QList< QDomNode > XHTMLDoc::DeepCopyNodeList( QDomNodeList node_list )
{
    QList< QDomNode > new_node_list;

    for ( int i = 0; i < node_list.count(); i++ )
    {
        new_node_list.append( node_list.at( i ).cloneNode() );
    }

    return new_node_list;
}
