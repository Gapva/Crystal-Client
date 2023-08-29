#include "../CrystalProfile.hpp"
#include <Geode/modify/PlayLayer.hpp>

std::vector<StartPosObject*> StartPoses;
std::vector<GameObject*> gravityPortals, dualPortals, gamemodePortals, miniPortals, speedChanges, mirrorPortals;
std::vector<bool> willFlip;

void SSPsetup() {
    willFlip.resize(StartPoses.size());
	size_t index = 0;
	for (StartPosObject* startPos : StartPoses) {
		for (size_t i = 0; i < gravityPortals.size(); i++)
		{
			if (gravityPortals[i]->getPositionX() - 10 > startPos->getPositionX())
				break;
			if (gravityPortals[i]->getPositionX() - 10 < startPos->getPositionX())
				willFlip[index] = gravityPortals[i]->m_objectID == 11;
		}

		startPos->m_levelSettings->m_startDual = PlayLayer::get()->m_levelSettings->m_startDual;
		for (size_t i = 0; i < dualPortals.size(); i++)
		{
			if (dualPortals[i]->getPositionX() - 10 > startPos->getPositionX())
				break;
			if (dualPortals[i]->getPositionX() - 10 < startPos->getPositionX())
				startPos->m_levelSettings->m_startDual = dualPortals[i]->m_objectID == 286;
		}
		startPos->m_levelSettings->m_startMode = PlayLayer::get()->m_levelSettings->m_startMode;
		for (size_t i = 0; i < gamemodePortals.size(); i++)
		{
			if (gamemodePortals[i]->getPositionX() - 10 > startPos->getPositionX())
				break;
			if (gamemodePortals[i]->getPositionX() - 10 < startPos->getPositionX())
			{
				switch (gamemodePortals[i]->m_objectID)
				{
				case 12:
					startPos->m_levelSettings->m_startMode = (int)IconType::Cube;
					break;
				case 13:
					startPos->m_levelSettings->m_startMode = (int)IconType::Ship;
					break;
				case 47:
					startPos->m_levelSettings->m_startMode = (int)IconType::Ball;
					break;
				case 111:
					startPos->m_levelSettings->m_startMode = (int)IconType::Ufo;
					break;
				case 660:
					startPos->m_levelSettings->m_startMode = (int)IconType::Wave;
					break;
				case 745:
					startPos->m_levelSettings->m_startMode = (int)IconType::Robot;
					break;
				case 1331:
					startPos->m_levelSettings->m_startMode = (int)IconType::Spider;
					break;
				}
			}
		}

		startPos->m_levelSettings->m_startMini = PlayLayer::get()->m_levelSettings->m_startMini;
		for (size_t i = 0; i < miniPortals.size(); i++)
		{
			if (miniPortals[i]->getPositionX() - 10 > startPos->getPositionX())
				break;
			if (miniPortals[i]->getPositionX() - 10 < startPos->getPositionX())
				startPos->m_levelSettings->m_startMini = miniPortals[i]->m_objectID == 101;
		}

		startPos->m_levelSettings->m_startSpeed = PlayLayer::get()->m_levelSettings->m_startSpeed;
		for (size_t i = 0; i < speedChanges.size(); i++)
		{
			if (speedChanges[i]->getPositionX() - 50 > startPos->getPositionX())
				break;
			if (speedChanges[i]->getPositionX() - 50 < startPos->getPositionX())
			{
				switch (speedChanges[i]->m_objectID)
				{
				case 200:
					startPos->m_levelSettings->m_startSpeed = Speed::Slow;
					break;
				case 201:
					startPos->m_levelSettings->m_startSpeed = Speed::Normal;
					break;
				case 202:
					startPos->m_levelSettings->m_startSpeed = Speed::Fast;
					break;
				case 203:
					startPos->m_levelSettings->m_startSpeed = Speed::Faster;
					break;
				case 1334:
					startPos->m_levelSettings->m_startSpeed = Speed::Fastest;
					break;
				}
			}
		}
		index++;
	}
}

class $modify(PlayLayer) {
    void addObject(GameObject* g) {
        PlayLayer::addObject(g);
        switch (g->m_objectID) {
			case 10:
			case 11:
				gravityPortals.push_back(g);
				break;
			case 12:
			case 13:
			case 47:
			case 111:
			case 660:
			case 745:
			case 1331:
				gamemodePortals.push_back(g);
				break;
            case 31:
                StartPoses.push_back(static_cast<StartPosObject*>(g));
                break;
			case 45:
			case 46:
				mirrorPortals.push_back(g);
				break;
			case 99:
			case 101:
				miniPortals.push_back(g);
				break;
			case 286:
			case 287:
				dualPortals.push_back(g);
				break;
			case 200:
			case 201:
			case 202:
			case 203:
			case 1334:
				speedChanges.push_back(g);
				break;
		}
    }

    bool init(GJGameLevel* gj) {
        if (!PlayLayer::init(gj)) return false;
        
        if (getVar<bool>("smart_startpos")) SSPsetup();

        return true;
    }

    void onQuit() {
        PlayLayer::onQuit();

        StartPoses.clear();
        gamemodePortals.clear();
        mirrorPortals.clear();
        miniPortals.clear();
        dualPortals.clear();
        speedChanges.clear();
        gravityPortals.clear();
        willFlip.clear();
    }
};