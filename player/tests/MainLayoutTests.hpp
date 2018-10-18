#include "test_utils.hpp"

#include "control/MainLayout.hpp"

#include "mocks/MockOverlayAdaptor.hpp"
#include "mocks/MockBackground.hpp"
#include "mocks/MockImageAdaptor.hpp"
#include "mocks/MockMediaContainer.hpp"
#include "mocks/MockFixedLayoutAdaptor.hpp"

testing::NiceMock<MockMediaContainer>* createMediaContainer();

const std::vector<std::vector<int>> zorders = {
    {10,9,8},
    {1,2,4,10},
    {10,7,9,1},
    {5,4},
    {1},
    {4,1,5,2},
    {4,3,2,1,0}
};

const auto invalidMainLayoutPos = invalidPositions<DEFAULT_WIDTH, MIN_X_POS, DEFAULT_HEIGHT, MIN_Y_POS>;

class MainLayoutTestPos : public testing::TestWithParam<Point> { };

class MainLayoutReorderTest : public testing::TestWithParam<std::vector<int>>
{
public:
    void addContainer(IMainLayout& layout, int zorder)
    {
        auto container = createMediaContainer();

        ON_CALL(*container, zorder()).WillByDefault(testing::Return(zorder));
        layout.addMediaContainer(unique(container), DEFAULT_XPOS, DEFAULT_YPOS);

        pushContainerAndSort(container);
    }

    testing::NiceMock<MockMediaContainer>* container(size_t index)
    {
        return m_containers[index];
    }

private:
    void pushContainerAndSort(testing::NiceMock<MockMediaContainer>* container)
    {
        m_containers.push_back(container);
        std::sort(m_containers.begin(), m_containers.end(), [=](const auto& first, const auto& second){
            return first->zorder() < second->zorder();
        });
    }

private:
    std::vector<testing::NiceMock<MockMediaContainer>*> m_containers;

};
