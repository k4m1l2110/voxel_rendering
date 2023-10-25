#ifndef VOXEL_GRID_H_
#define VOXEL_GRID_H_

#include <glm/glm.hpp>
#include <glm/gtc/noise.hpp>
#include "../glad/glad.h"
#include <GLFW/glfw3.h>
#include "../shaders/shader.hpp"
#include "../shaders/camera.h"
#include "../obj/block.h"
#include <random>
#include <cmath>
#include <ctime>
#include <vector>

class VoxelGrid {
public:
    VoxelGrid(float width, float height, float depth, Mesh &m)
            : width_(width), height_(height), depth_(depth), mesh(m) {
        float block_size=0.2f;
        /*for (float w = 0; w < width/10.; w+=block_size) {
            for (float h = 0; h < height/10.; h+=block_size) {
                for (float d = 0; d < depth/10.; d+=block_size) {
                    blocks_.push_back({glm::vec3(w, d, h), mesh});
                }
            }
        }*/
        for (float w = 0; w < width/5.; w+=block_size) {
            for (float h = 0; h < height/5.; h+=block_size) {
                float worldX = static_cast<float>(w) * blockSize;
                float worldY = static_cast<float>(h) * blockSize;

                float noiseValue = glm::perlin(glm::vec2(worldX * 0.1f, worldY * 0.1f));
                float blockHeight = noiseValue * depth;

                blocks_.push_back({glm::vec3(w, blockHeight, h), mesh});
            }
        }
    }
    const Block& GetBlock(int x, int y, int z) const {
        return blocks_[GetIndex(x, y, z)];
    }

    /*void SetBlock(int x, int y, int z, const Block& block) {
        blocks_[GetIndex(x, y, z)] = block;
    }*/

    int GetWidth() const {
        return width_;
    }

    int GetHeight() const {
        return height_;
    }

    int GetDepth() const {
        return depth_;
    }

    void DrawVoxelGrid(Shader& shader, Light &light, Camera& camera) {
        for (auto &b:blocks_){
            b.Draw(shader,light,camera);
        }
    }

private:
    Mesh &mesh;
    float width_;
    float height_;
    float depth_;
    std::vector<Block> blocks_;
    int GetIndex(int x, int y, int z) const {
        return x + (y * width_) + (z * width_ * height_);
    }
    float scale = 1.;
    float blockSize = 0.2f;

};
#endif