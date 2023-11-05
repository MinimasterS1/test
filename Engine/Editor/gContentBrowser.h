#pragma once


#ifndef CONTENT_BROWSER_H
#define CONTENT_BROWSER_H

#include "gEditor.h"


#include <functional>
#include <filesystem>

namespace fs = std::filesystem;



class ContentBrowser : public EditorAPI
{
public:


    ContentBrowser() {};

    void DrawBrowser();
    void DrawFolderTree(const fs::path& directory, int level);

    void LoadOnScene(const std::vector<fs::path>& filePaths,

        const std::vector<glm::vec3>& initialPositions,
        const std::vector<glm::vec3>& initialScale,
        const std::vector<glm::vec3>& initialRotation);

    void SelectedFile(const fs::path& filePath);

    std::string ConvertToRelativePath(const std::string& fullPath);


  
    void DrawProperties();

    void AddObjectToData(int index, const glm::vec3& position, const glm::vec3& scale, const glm::vec3& rotation);

    void DrawSceneObjects();

    int selectedObjectIndex = -1;

    void UpdateObjectData();

    struct ObjectInfo {
        int index;

        glm::vec3 position;
        glm::vec3 scale;
        glm::vec3 rotation;
        std::string objectName;
    };


    std::vector<ObjectInfo> objectData;




private:

    std::vector<glm::vec3> initialPositions;
    std::vector<glm::vec3> initialScale;
    std::vector<glm::vec3> initialRotation;

    std::string fileSerializeName;


};

#endif 