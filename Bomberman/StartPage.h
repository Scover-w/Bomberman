#pragma once
#include "headersProject.h"


class StartPage
{
private:
	string history = "                                    La vie éternelle est apparu il y a un peu plus de 500 ans.\n                La technologie qui a permis ce miracle s'appelle le TDC ou Transfert de Conscience.\n                                         En transferant la conscience de corps en corps, \n                                          les humains n'ont maintenant plus aucune limite.\n\n                                                    Ou devrais-je dire... certains humains. \n\n                                  En effet, peu de personnes peuvent s'offrir cette technologie. \n                                  Cela à conduit inéxorablement à la création de deux castes : \n                                                            les Maths et les Indigents.\n                    Cette exacerbation des inégalités s'est tellement creusé que les deux castes\n                                                      n'ont plus rien en commun.\n                                  Les Maths pensent que les Indigents sont des animaux,\n                                tandis que les Indigents pensent que les Maths sont des dieux.\n\n                                     Après plus de 200 ans, les Maths ont commencés à s'ennuyer. \n                               Après, avoir tout fait, tout vécût, leur vie est devenue insupportable. \n\n                                 Lorsque l'on arrive plus à éprouver du bonheur nous-même,\n                                on ne peut que éprouver du bonheur sur le malheur des autres.\n\n                                           C'est pourquoi, les Maths ont créer le jeu Bomberman. \n\n                                  Le but du jeu est de rassembler plusieurs Indigents dans une arène. \n                                                       L'objectif : le dernier en vie gagne.\n                                      Les Indigents ont pour arme principale des bombes.\n               L'indigent qui gagne cinq parties d'affilées pourra passer 10 ans au côté des Maths.\n\n\n                                                              Il sera appelé : Bomberman.";

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

