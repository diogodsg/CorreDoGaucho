#include "stdafx.h"
#include "TelaMorte.h"

// _______________________________________________________________________________
TelaMorte::TelaMorte(JogoInfo* pji, int s)
	:Ente(pji), score(s)
{
	this->iniciarTextos();
}

// _______________________________________________________________________________
TelaMorte::~TelaMorte()
{
}

// _______________________________________________________________________________
void TelaMorte::iniciarTextos()
{
	this->nomeInput = "";

	// carrega a fonte
	if (!this->fonte.loadFromFile("./Recursos/Fontes/Bebas.ttf")) {
		std::cout << "PONTUACAO::FALHA AO CARREGAR FONTE" << std::endl;
	}
	// inicia texto morte
	this->textoMorte.setFont(this->fonte);
	this->textoMorte.setString("VOCE MORREU!!!");
	this->textoMorte.setCharacterSize(100);
	this->textoMorte.setFillColor(sf::Color::Red);
	this->textoMorte.setPosition(TAM_JANELA_X / 2.f - this->textoMorte.getGlobalBounds().width / 2.f, 100.f);

	// inicia texto score
	this->textoScore.setFont(this->fonte);
	this->textoScore.setString("SCORE: " + std::to_string(score));
	this->textoScore.setCharacterSize(50);
	this->textoScore.setFillColor(sf::Color::White);
	this->textoScore.setPosition(TAM_JANELA_X / 2.f - this->textoScore.getGlobalBounds().width / 2.f, 250.f);

	// inicia texto Digite seu nome;
	this->digiteNome.setFont(this->fonte);
	this->digiteNome.setString("Digite seu nome: ");
	this->digiteNome.setCharacterSize(50);
	this->digiteNome.setFillColor(sf::Color::White);
	this->digiteNome.setPosition(TAM_JANELA_X / 2.f - this->textoMorte.getGlobalBounds().width / 2.f, TAM_JANELA_Y / 2.f);

	// inicia texto nome
	this->nome.setFont(this->fonte);
	this->nome.setString(this->nomeInput);
	this->nome.setCharacterSize(50);
	this->nome.setFillColor(sf::Color::White);
	this->nome.setPosition(this->digiteNome.getPosition().x + this->digiteNome.getGlobalBounds().width + 10.f, TAM_JANELA_Y / 2.f);
}

// _______________________________________________________________________________
void TelaMorte::adicionarPontuacao()
{
	/* Adiciona uma nova pontua��o no arquivo de pontuacoes */
	std::ofstream arquivo_pontuacao;
	arquivo_pontuacao.open("./Recursos/dados/pontuacao.txt", std::ios::out | std::ios::app);
	arquivo_pontuacao << "\n" << this->nomeInput << " " << this->score;
	arquivo_pontuacao.close();
}

// _______________________________________________________________________________
void TelaMorte::atualizar()
{
}

// _______________________________________________________________________________
void TelaMorte::atualizarEventos(sf::Event& evento_sfml)
{
	/* Checa por eventos SFML*/
	if (evento_sfml.type == sf::Event::KeyReleased)
	{
		// adiciona a nova pontua��o e vai a tela de pontuacao
		if (evento_sfml.key.code == sf::Keyboard::Enter && this->nomeInput.size() >= 3) {
			this->adicionarPontuacao();
			this->jogoInfo->getTocaDisco()->tocarMusicaInicio();
			this->jogoInfo->trocarEnte(new Pontuacao(this->jogoInfo)); 
		}
	}
	// recebe input do usuario
	else if (evento_sfml.type == sf::Event::TextEntered) 
	{
		if (evento_sfml.text.unicode == '\b' && this->nomeInput.size() > 0) // tecla backspace
			this->nomeInput.erase(this->nomeInput.size() - 1, 1);
		else if (((evento_sfml.text.unicode > 64) && (evento_sfml.text.unicode < 91)) // maisculas
			|| ((evento_sfml.text.unicode > 96) && (evento_sfml.text.unicode < 123))) // minusculas
			this->nomeInput += evento_sfml.text.unicode;

		// texto nome recebe o conteudo do input
		this->nome.setString(this->nomeInput);
	}
}

// _______________________________________________________________________________
void TelaMorte::desenhar(sf::RenderTarget& janela)
{
	/*Desenha todos os textos na tela*/
	janela.draw(this->textoMorte);
	janela.draw(this->textoScore);
	janela.draw(this->digiteNome);
	janela.draw(this->nome);
}