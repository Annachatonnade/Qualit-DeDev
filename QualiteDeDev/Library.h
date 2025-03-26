// Library.h - Module de gestion de la biblioth�que
#pragma once
#include <vector>
#include <map>
#include <string>
#include "Document.h"
#include "FileSystem.h"

class Library {
private:
    std::map<std::string, Document> documents;
    FileSystem* fileSystem;
    std::string basePath;

public:
    Library(FileSystem* fs, const std::string& path)
        : fileSystem(fs), basePath(path) {
    }

    bool addDocument(const Document& doc) {
        std::string title = doc.getTitle();
        if (title.empty() || documents.find(title) != documents.end()) {
            return false;
        }

        // Cr�er une copie du document et lui assigner le fileSystem
        Document newDoc = doc;
        newDoc.setFileSystem(fileSystem);
        documents[title] = newDoc;

        return documents[title].save(basePath + "/" + title + ".doc");
    }

    Document* getDocument(const std::string& title) {
        auto it = documents.find(title);
        return (it != documents.end()) ? &(it->second) : nullptr;
    }

    bool loadLibrary() {
        // Dans une impl�mentation r�elle, on scannerait le r�pertoire
        // Pour cet exemple, nous supposerons que nous avons des fichiers pr�d�finis
        return true;
    }
};
