#pragma once
#include "headersProject.h"


class StartPage
{
private:
	string history = "                                    La vie �ternelle est apparu il y a un peu plus de 500 ans.\n                La technologie qui a permis ce miracle s'appelle le TDC ou Transfert de Conscience.\n                                         En transferant la conscience de corps en corps, \n                                          les humains n'ont maintenant plus aucune limite.\n\n                                                    Ou devrais-je dire... certains humains. \n\n                                  En effet, peu de personnes peuvent s'offrir cette technologie. \n                                  Cela � conduit in�xorablement � la cr�ation de deux castes : \n                                                            les Maths et les Indigents.\n                    Cette exacerbation des in�galit�s s'est tellement creus� que les deux castes\n                                                      n'ont plus rien en commun.\n                                  Les Maths pensent que les Indigents sont des animaux,\n                                tandis que les Indigents pensent que les Maths sont des dieux.\n\n                                     Apr�s plus de 200 ans, les Maths ont commenc�s � s'ennuyer. \n                               Apr�s, avoir tout fait, tout v�c�t, leur vie est devenue insupportable. \n\n                                 Lorsque l'on arrive plus � �prouver du bonheur nous-m�me,\n                                on ne peut que �prouver du bonheur sur le malheur des autres.\n\n                                           C'est pourquoi, les Maths ont cr�er le jeu Bomberman. \n\n                                  Le but du jeu est de rassembler plusieurs Indigents dans une ar�ne. \n                                                       L'objectif : le dernier en vie gagne.\n                                      Les Indigents ont pour arme principale des bombes.\n               L'indigent qui gagne cinq parties d'affil�es pourra passer 10 ans au c�t� des Maths.\n\n\n                                                              Il sera appel� : Bomberman.";

	Text storyText;
	Vector2f positionText;

	Texture shaderT;
	Sprite shaderS;

	Shader shader;

	sf::Clock clk;

	float timeSpent = 0.0f;

public:
	StartPage();
	~StartPage();

	void Update();
	void DrawText();
};

