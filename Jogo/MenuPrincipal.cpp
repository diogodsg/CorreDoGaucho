#include "stdafx.h"
#include "MenuPrincipal.h"

// _______________________________________________________________________________
MenuPrincipal::MenuPrincipal(JogoInfo* pji):
	Ente(pji)
{
	this->botaoAtivo = novo_jogo;
	this->iniciarBotoes();
	this->iniciarBackground("./Recursos/Imagens/backgrounds/menu.png");
}

// _______________________________________________________________________________
MenuPrincipal::~MenuPrincipal()
{
	this->jogoInfo = NULL;
	// desaloca botoes
	for (auto& botao : this->botoes)
		delete botao.second;
}

// _______________________________________________________________________________
void MenuPrincipal::iniciarBotoes()
{
	/* Inicia todos os botoes do menu principal */
	this->botoes[novo_jogo] = new gui::Botao(this->jogoInfo->getJanela()->getSize().x / 2 - 100.f, 200.f, "Novo Jogo");
	this->botoes[escolha_de_fases] = new gui::Botao(this->jogoInfo->getJanela()->getSize().x / 2 - 100.f, 255.f, "Escolher Fase");
	this->botoes[lista_de_pontuacoes] = new gui::Botao(this->jogoInfo->getJanela()->getSize().x / 2 - 100.f, 320.f, "Pontua��o");
	this->botoes[sair] = new gui::Botao(this->jogoInfo->getJanela()->getSize().x / 2 - 100.f, 380.f, "Sair");
	this->botoes[sair]->setCorAtivado(sf::Color::Red); // botao sair ser� vermelho quando ativo

	// Inicia a caixa que contem os botoes
	this->caixaBotoes.setFillColor(sf::Color(0, 0, 0, 150));
	this->caixaBotoes.setSize(sf::Vector2f(300.f, 270.f));
	this->caixaBotoes.setPosition(this->jogoInfo->getJanela()->getSize().x /2 - this->caixaBotoes.getGlobalBounds().width / 2, 180.f);

	this->botoes[this->botaoAtivo]->ativar();
}

// _______________________________________________________________________________
void MenuPrincipal::atualizar()
{
}

// _______________________________________________________________________________
void MenuPrincipal::atualizarEventos(sf::Event& evento_sfml)
{
	/* Checa por eventos SFML*/
	if (evento_sfml.type == sf::Event::KeyReleased)
	{
		if (evento_sfml.key.code == sf::Keyboard::Up)
			this->trocarBotao(-1); // ativa o botao de cima
		if (evento_sfml.key.code == sf::Keyboard::Down)
			this->trocarBotao(1); // ativa o botao de baixo
		if (evento_sfml.key.code == sf::Keyboard::Enter)
			this->GerenciarCliqueBotao();
	}
}

// _______________________________________________________________________________
void MenuPrincipal::trocarBotao(int direcao)
{
	/* Muda o botao ativo */

	// desativa o botao atual
	this->botoes[this->botaoAtivo]->desativar();

	// troca o botao ativo
	if (this->botaoAtivo + direcao >= 0)
		this->botaoAtivo = (this->botaoAtivo + direcao) % static_cast<int>(this->botoes.size());
	else
		this->botaoAtivo = static_cast<int>(this->botoes.size()) - 1;

	// ativa o novo botao atual
	this->botoes[this->botaoAtivo]->ativar();
}

// _______________________________________________________________________________
void MenuPrincipal::GerenciarCliqueBotao()
{
	/* Realiza a a��o vinculada com o botao ativo */

	if (this->botaoAtivo == novo_jogo)
		this->jogoInfo->pushEnte(static_cast<Ente* >(new VelhoOeste(this->jogoInfo)));
	
	else if(this->botaoAtivo == escolha_de_fases)
		this->jogoInfo->pushEnte(static_cast<Ente*>(new MenuEscolhaFases(this->jogoInfo)));

	else if (this->botaoAtivo == lista_de_pontuacoes)
		this->jogoInfo->pushEnte(static_cast<Ente* >(new Pontuacao(this->jogoInfo)));

	else if (this->botaoAtivo == sair)
		this->jogoInfo->fecharJanela();
}

// _______________________________________________________________________________
void MenuPrincipal::desenhar(sf::RenderTarget& janela)
{
	/* Desenha o novo frame na janela */

	janela.draw(this->background);
	janela.draw(this->caixaBotoes);

	// desenha botoes
	for (auto& botao : this->botoes)
		botao.second->desenharBotao(janela);
}
