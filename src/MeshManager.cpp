#include <string>
#include "MeshManager.h"
#include "Mesh.h"
#include "OBJLoader.h"

void MeshManager::addMesh(const std::string& file){
	std::string filename = fs::path(file).stem();

    if(loader->LoadFile(file)){

		// Go through each loaded mesh and out its contents
		for (size_t i = 0; i < loader->LoadedMeshes.size(); i++)
		{
			// Copy one of the loaded meshes to be our current mesh
			objl::Mesh curMesh = loader->LoadedMeshes[i];

			std::string name = filename + "." + curMesh.MeshName;

			if(meshes.find(name) != meshes.end()){
				std::cout << "duplicate mesh name : " << name << " (ignoring duplicates)" << std::endl; 
				continue;
			}
			std::cout << "mesh: " << name << std::endl;
			
			Mesh* m = new Mesh(curMesh.Vertices.size(),
						  (float*)&(curMesh.Vertices[0].Position),
						  (float*)&(curMesh.Vertices[0].Normal),
						  (float*)&(curMesh.Vertices[0].TextureCoordinate),
						  8, 
						  curMesh.Indices.size(),
						  curMesh.Indices.data());
			
			meshes.insert(std::make_pair(name, m));
			
		}
    }

}

MeshManager::MeshManager(const std::string& dir){
	loader = new objl::Loader();
    addDir(dir);
}

void MeshManager::addDir(const std::string& dir){
    for (const auto & entry : fs::directory_iterator(dir)){

        if(entry.is_directory())
            addDir(entry.path());
        else if(entry.path().extension() == ".obj")
            addMesh(entry.path());
    }
}

MeshManager::~MeshManager(){
	for(auto m : meshes){
		delete m.second;
	}
	delete loader;
}
AbstractMesh* MeshManager::getMesh(const std::string& name){
	auto it = meshes.find(name);
	if(it == meshes.end()){
		std::cout << "DEBUG: " << name << " does not exist" << std::endl;

		return 0;
	}
	else{
		std::cout << "DEBUG: "  << name << " found" << std::endl;

		return it->second;
	}
}