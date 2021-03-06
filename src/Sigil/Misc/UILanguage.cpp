/************************************************************************
**
**  Copyright (C) 2011  John Schember <john@nachtimwald.com>
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

#include <QtCore/QDir>
#include <QtCore/QCoreApplication>
#include <QtCore/QLibraryInfo>
#include <QtCore/QString>
#include "Misc/UILanguage.h"

#ifdef Q_WS_X11
#include <stdlib.h>
#endif

static QString TRANSLATION_FILE_PREFIX = "sigil_";
static QString TRANSLATION_FILE_SUFFIX = ".qm";

QStringList UILanguage::GetPossibleTranslationPaths()
{
    // There are a few different places translations can be stored depending
    // on the platform and where they were installed.
    QStringList possible_qm_locations;

    #ifdef Q_WS_X11
    // The user can specify an env variable that points to the translation.
    const QString env_qm_location = QString(getenv("SIGIL_TRANSLATIONS"));
    if (!env_qm_location.isEmpty())
    {
        possible_qm_locations.append(env_qm_location);
    }

    // Possible location if the user installed from source.
    // This really should be changed to be passed the install prefix given to
    // cmake instead of guessing based upon the executable path.
    possible_qm_locations.append(QCoreApplication::applicationDirPath() + "/../share/" + QCoreApplication::applicationName().toLower() + "/translations/");
    #endif

    possible_qm_locations.append(QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    possible_qm_locations.append(QCoreApplication::applicationDirPath() + "/translations");

    return possible_qm_locations;
}

QStringList UILanguage::GetUILanguages()
{
    QStringList ui_languages;

    foreach (QString path, GetPossibleTranslationPaths()) {
        // Find all translation files and add them to the avaliable list.
        QDir translationDir(path);
        if (translationDir.exists())
        {
            QStringList filters;
            // Look for all .qm files.
            filters << TRANSLATION_FILE_PREFIX % "*" % TRANSLATION_FILE_SUFFIX;
            translationDir.setNameFilters(filters);
            QStringList translation_files = translationDir.entryList();
            foreach (QString file, translation_files )
            {
                QFileInfo fileInfo(file);
                QString basename = fileInfo.baseName();
                QString language = basename.right(basename.length() - TRANSLATION_FILE_PREFIX.length());
                ui_languages.append(language);
            }
        }
    }
    return ui_languages;
}
