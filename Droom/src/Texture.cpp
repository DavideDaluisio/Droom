#include "Texture.h"


Texture::Texture(const char* imageFile, const char* texType, GLuint slot)
{
	int widthImg, heightImg, numColCh;

	// Imposta l'opzione per capovolgere verticalmente l'immagine al caricamento
	// (utile perché OpenGL considera l'origine in basso a sinistra, mentre molte immagini hanno l'origine in alto a sinistra)
	stbi_set_flip_vertically_on_load(true);

	// stbi_load(...) è una funzione della libreria stb_image.h che carica un'immagine da file.
	// Restituisce un puntatore a un array di byte (unsigned char*) che contiene i pixel dell'immagine,
	// letti uno dopo l'altro da sinistra a destra, riga per riga, dall'alto verso il basso (a meno che non si imposti il flip verticale).
	//
	// Ogni pixel è composto da 1, 2, 3 o 4 byte, a seconda del numero di canali dell'immagine:
	// - 1 canale  ? scala di grigi
	// - 3 canali ? RGB
	// - 4 canali ? RGBA (RGB + trasparenza)
	//
	// I parametri passati per riferimento (widthImg, heightImg, numColCh) verranno riempiti automaticamente
	// con i dati corrispondenti a: larghezza, altezza e numero di canali per pixel.
	//
	// Il valore restituito (imageData) è una sequenza continua di byte in RAM che rappresentano tutti i pixel dell'immagine,
	// utile per caricarla successivamente nella GPU con funzioni come glTexImage2D.
	//
	// IMPORTANTE: Dopo l'uso, la memoria va liberata con stbi_image_free(imageData).
	unsigned char* imageData = stbi_load(imageFile, &widthImg, &heightImg, &numColCh, 0);

	// Genera una texture all'interno della GPU
	glGenTextures(1, &ID);
	// Attiva l'unità di texture specificata (slot è un numero intero, es. 0, 1, 2...) dicendo 
	// a OpenGL che tutte le operazioni sulle texture da qui in poi useranno GL_TEXTURE0 + slot.
	// È fondamentale se stai usando più texture nello stesso shader (es. per ambient occlusion, normal map, ecc.)
	glActiveTexture(GL_TEXTURE0 + slot);
	unit = slot;
	glBindTexture(GL_TEXTURE_2D, ID);
	
	// Imposta il filtro quando la texture viene rimpicciolita (mipmap + campionamento NEAREST)
	// e quando viene ingrandita (campionamento NEAREST senza mipmap)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Imposta la modalità di ripetizione della texture su entrambi gli assi (S e T)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Carica i dati dell'immagine nella texture in base al numero di canali: 
	// usa GL_RGBA per immagini con trasparenza, GL_RGB per immagini a colori, e GL_RED per immagini in scala di grigi.
	if (numColCh == 4)
		glTexImage2D
		(
			GL_TEXTURE_2D,
			0,
			GL_RGBA,
			widthImg,
			heightImg,
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			imageData
		);
	else if (numColCh == 3)
		glTexImage2D
		(
			GL_TEXTURE_2D,
			0,
			GL_RGBA,
			widthImg,
			heightImg,
			0,
			GL_RGB,
			GL_UNSIGNED_BYTE,
			imageData
		);
	else if (numColCh == 1)
		glTexImage2D
		(
			GL_TEXTURE_2D,
			0,
			GL_RGBA,
			widthImg,
			heightImg,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			imageData
		);
	else
		throw std::invalid_argument("Automatic Texture type recognition failed");

	// Genera automaticamente tutti i livelli di mipmap per la texture attualmente bindata
	glGenerateMipmap(GL_TEXTURE_2D);

	// Libera la memoria dell'immagine in RAM, ora che è stata caricata nella GPU
	stbi_image_free(imageData);

	// Scollega la texture 2D corrente, per evitare modifiche accidentali
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
	glDeleteTextures(1, &ID);
}

void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	shader.setInt(uniform, unit);
}

void Texture::Bind()
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

