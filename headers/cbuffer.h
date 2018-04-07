#ifndef CBUFFER_H
#define CBUFFER_H

#include <algorithm>
#include <iostream>
#include <cstddef>
#include <cstring>
#include <functional>

#define NDEBUG
/**
	@file cbuffer.h

	@brief Definizione della classe cbuffer

	Definizione della classe cbuffer. la classe rappresenta un buffer circolare implementato tramite liked list.
**/

template <typename T> class cbuffer {

	typedef unsigned int size_type;
	typedef T * value_type;

	/**
		@brief Cella del cbuffer

		Struttura che costituisce una singola cella di memoria del cbuffer.
	**/
	struct cell	{
		T value;
		cell * next;

		cell() : next(0) {}

		cell (const T &v, cell *n = 0) : value(v), next(n) {}
	};

	cell * _head;
	cell * _tail;
	unsigned int _size;
	unsigned int _elements;

public:

	/**
		@brief Costruttore di default (METODO FONDAMENTALE)

		Costruttore che permette di instanziare un cbuffer vuoto.
	**/
	cbuffer() : _head(0), _tail(0), _size(0), _elements(0) {
		#ifndef NDEBUG
			std::cout << "cbuffer::cbuffer()" << std::endl;
		#endif
	}

	/**
		@brief Costruttore secondario (size)

		Costruttore che permette di secificare la dimensione del cbuffer da istanziare.

		@param size Dimensione del cbuffer
	**/
	explicit cbuffer(size_type size)
		:_head(0)
		,_tail(0)
		,_size(0)
		,_elements(0)
		{
		_size = size;
		#ifndef NDEBUG
			std::cout << "cbuffer::cbuffer(syze_type size)" << std::endl;
		#endif
	}

	/**
		@brief Copy constructor (METODO FONDAMENTALE)

		Permette di istanziare un cbuffer come copia del cbuffer fornito in input. Nel caso di fallimento il cbuffer parzialmente popolato viene distrutto per mezzo dell'invocazione alla funzione clear, in modo da prevenire eventuali allocazioni di memoria non gestite.

		@param &other Reference al cbuffer di cui eseguire la copia.
	**/
	cbuffer(const cbuffer &other) :_head(0), _size(0) {
		#ifndef NDEBUG
			std::cout << "cbuffer::cbuffer(const cbuffer &other)" << std::endl;
		#endif

		const cell *tmp = other._head;
		_size = other._size;
		_elements = 0;
		try	{
			while(tmp != 0 && _elements < other._size) {
				insert(tmp->value);
				tmp = tmp->next;
			}
		}
		catch (...) {
			clear();
			throw;
		}
	}

	/**
		@brief Operatore di assegnamento

		Ridefinizione dell'operatore di assegnamento tra cbuffer.
		Operatore che sovrascrive il contenuto del primo memnro col contenuto del secondo.

		@param &other reference al cbuffer di cui eseguire l'assegnamento.
	**/
	cbuffer& operator=(const cbuffer &other) {
		#ifndef NDEBUG
			std::cout << "cbuffer::operator=(const cbuffer &other)" << std::endl;
		#endif
		try {
			if (this->_head != other._head) {
			cbuffer tmp(other);
			std::swap(tmp._head, _head);
			std::swap(tmp._tail, _tail);
			std::swap(tmp._size, _size);
			std::swap(tmp._elements, _elements);
		    }
		}
		catch (...) {
			clear();
			throw;
		}
		return *this;
	}

	/**
		@brief Distruttore (METODO FONDAMENTALE)

		Distruttore che libera la memoria associata ad un cbuffer quando questo esce dallo scope.
	**/
	~cbuffer() {
		#ifndef NDEBUG
			std::cout << "cbuffer::~cbuffer()" << std::endl;
		#endif
		clear();
	}

	/**
		@brief clear

		Funzione che permette di deallocare la memoria riservata ad un cbuffer eliminando ogni cella del cbuffer.
		Per sicurezza il puntatore e la dimensione vengono reinizializzati a null.
	**/
	void clear() {
		cell* tmp = _head;
		while(tmp != 0 && _elements > 0) {
			cell* c = tmp->next;
			delete tmp;
			tmp = c;
			_elements--;
		}
		_head = 0;
		_tail = 0;
		_size = 0;
	}

	/**
		@brief Inserimento di valori

		Fuzione che permette di inserire dei valori in un cbuffer.
		Il metodo inserisce una cella in testa al cbuffer se questo è vuoto,
		nella prima posizione utile se vi sono altri elementi ed esegue un inserimento in coda cancellando l'elemento più vecchio se il cbuffer è pieno.

		@param &value Reference al valore da inserire nel cbuffer.
	**/
	void insert(const T &value) {
		#ifndef NDEBUG
			std::cout << "insert(const T &value)" << std::endl;
		#endif

		cell * c = new cell(value);

		if(isEmpty()) {
			#ifndef NDEBUG
				std::cout << "Inserisco in cbuffer vuoto" << std::endl;
			#endif
			_head = _tail = c;
			_elements++;
			return;
		}

		if (isFull()) {
			#ifndef NDEBUG
				std::cout<<"Sovrascrivi testa" << std::endl;
			#endif
			_tail->next = c;
			c->next = _head->next;
			delete _head;
			_head = c->next;
			_tail = c;
			return;
		}

		#ifndef NDEBUG
			std::cout << "Trovato spazio vuoto" << std::endl;
		#endif

		_tail->next = c;
		_elements++;
		if(_elements == _size){
			c->next = _head;
		}
		_tail = c;
	}

	/**
		@brief Numero di elementi nel cbuffer

		Ritorna il numero di elementi attualmente nel cbuffer.

		@return int Numero di elementi contenuti nel cbuffer.
	**/
	const int getElements(){
		return _elements;
	}

	const int getElements() const {
		return _elements;
	}

	/**
		@brief Dimensione massima

		Ritorna la dimensione massima del cbuffer definita in fase di costruzione.

		@return int Dimensione massima del cbuffer.
	**/
	const int getSize(){
		return _size;
	}

	const int getSize() const{
		return _size;
	}

	/**
		@brief Buffer pieno

		Determina se il cbuffer è pieno.

		@return bool true per cbuffer pieno, false altrimenti.
	**/
	bool isFull() {
		if(_tail->next == _head){
			return _elements == _size;
		}
		return false;
	}

	/**
		@brief Cbuffer vuoto

		Determina se il cbuffer è vuoto.

		@return bool true se il cbuffer è vuoto, false altrimenti.
	**/
	bool isEmpty() {
		return _elements == 0;
	}


	/**
		@brief Rimozione in testAssegnamento

		Rimuove l'elemento attualmente in testa al cbuffer e sposta la testa di una posizione, fornendo un'indicazione sulla riuscita dell'operazione.
		In caso di riuscita decrementa di un'unità il numero di elementi nel cbuffer.

		@return bool true se la cancellazione è riuscita, false altrimenti.
	**/
	bool deleteFromHead () {
		#ifndef NDEBUG
			std::cout << "cbuffer::deleteFromHead()" << std::endl;
		#endif

		if(isEmpty()) {
			std::cout << "Can't remove elements from empty buffer!" << std::endl;
			return false;
		}

		else if (isFull()) {
			_tail->next = 0;
		}
		cell* tmp;
		tmp = _head;
		_head = _head->next;
		_elements--;
		delete tmp;
		return true;

	}

	/**
		@brief Accesso ai dati tramite []

		Ridefinizione dell'operatore [] per l'accesso ai dati del cbuffer.

		@param index Indice del dato a cui accedere

		@return T puntatore al campo value della cella indirizzata da index
	**/
	T &operator[](unsigned int index) {
		if(index > _size) {
			std::cout << "Specified index exceeds the buffer size!" << std::endl;
			throw;
		}
		cell* tmp = _head;
		for(int i=0; i < index; i++) {
			tmp = tmp->next;
		}
		return tmp->value;
	}

	T& operator[](unsigned int index) const {
		if(index > _size) {
			std::cout << "Specified index exceeds the buffer size!" << std::endl;
			throw;
		}
		cell* tmp = _head;
		for(int i=0; i < index; i++) {
			tmp = tmp->next;
		}
		return tmp->value;
	}

	/**
		@brief Costruttore da sequenza

		Costruttore che istanzia un cbuffer a partire da una sequenza genewrica di dati identificata da due iteratori.

		@param size Dimensione del cbuffer da instanziare.
		@param begin Iteratore di inizio sequenza.
		@param end iteratore di fine sequenza.
	**/
	template <typename IterT>
		cbuffer(size_type size, IterT begin, IterT end) : _head(0), _size(0), _elements(0) {
		try{
			_size = size;
			for(; begin!=end; ++begin) {
				insert(static_cast<T>(*begin));
			}

		} catch(...){
			clear();
			throw;
		}
	}

	class const_iterator {
		const cell* c;
		bool loop;
	public:
		typedef std::forward_iterator_tag iterator_category;
		typedef T                         value_type;
		typedef ptrdiff_t                 difference_type;
		typedef const T*                  pointer;
		typedef const T&                  reference;


		const_iterator() : c(0) {}

		const_iterator(const const_iterator &other) : c(other.c), loop(other.loop){}

		const_iterator& operator=(const const_iterator &other) {
			c = other.c;
			loop = other.loop;
			return *this;
		}

		~const_iterator() {
			c = 0;
		}

		reference operator*() const {
			return c->value;
		}

		pointer operator->() const {
			return &(c->value);
		}

		const_iterator operator++(int) {
			iterator tmp(*this);
			c = c->next;
			loop = true;
			return tmp;
		}

		const_iterator& operator++() {
			#ifndef NDEBUG
				std::cout << "Scorri in avanti con l'iteratore\n";
			#endif
			c = c->next;
			loop = true;
			return *this;
		}

		bool operator==(const const_iterator &other) const {
			return (c == other.c && loop == other.loop);
		}

		bool operator!=(const const_iterator &other) const {
			return (c != other.c || loop != other.loop);
		}

	private:

		friend class cbuffer;
		const_iterator(cell *c) : c(c), loop(false) {}
		const_iterator(cell *c, bool loop) : c(c), loop(loop) {}
	};

	class iterator {
		cell* c;
		bool loop;
	public:
		typedef std::forward_iterator_tag iterator_category;
		typedef T                         value_type;
		typedef ptrdiff_t                 difference_type;
		typedef T*                		  pointer;
		typedef T&                  	  reference;


		iterator() : c(0) {}

		iterator(const iterator &other) : c(other.c), loop(other.loop){}

		iterator& operator=(const iterator &other) {
			c = other.c;
			loop = other.loop;
			return *this;
		}

		~iterator() {
			c = 0;
		}

		reference operator*() {
			return c->value;
		}

		pointer operator->() {
			return &(c->value);
		}

		iterator operator++(int) {
			iterator tmp(*this);
			c = c->next;
			loop = true;
			return tmp;
		}

		iterator& operator++() {
			#ifndef NDEBUG
				std::cout << "Scorri in avanti con l'iteratore\n";
			#endif
			c = c->next;
			loop = true;
			return *this;
		}

		bool operator==(const iterator &other) const {
			return (c == other.c && loop == other.loop);
		}

		bool operator!=(const iterator &other) const {
			return (c != other.c || loop != other.loop);
		}

		void insert(const T &value) {
			c->value = value;
		}

	private:

		friend class cbuffer;
		iterator(cell *c) : c(c), loop(false) {}
		iterator(cell *c, bool loop) : c(c), loop(loop) {}

	};

	iterator begin() {
		#ifndef NDEBUG
			std::cout << "begin()\n";
		#endif
		return iterator(_head, false);
	}

	iterator end() {
		#ifndef NDEBUG
			std::cout << "end()\n";
		#endif
		if(_tail->next == _head) {
			return iterator(_head, true);
			}
		return iterator(_tail->next, true);
	}

	const_iterator begin() const{
		#ifndef NDEBUG
			std::cout << "begin()\n";
		#endif
		return const_iterator(_head, false);
	}

	const_iterator end() const {
		#ifndef NDEBUG
			std::cout << "end()\n";
		#endif
		if(_tail->next == _head) {
			return const_iterator(_head, true);
		}
		return const_iterator(_tail->next, true);
	}
};

	/**
		@brief Stampa di un cbuffer

		Ridefinizione dell'operatore << su un cbuffer. Scansiona tutti gli elemnti contenuti nel cbuffer ed estrae i relativi valori, inserendoli in uno stream di output.

		@param &os reference ad un output stream.
		@param &cb reference ad un cbuffer.

		@return ostream output stream contenente i valori di tutti gli lementi nel cbuffer.
	**/
	template <typename T>
	std::ostream &operator<<(std::ostream &os, const cbuffer<T> &cb){

		typename cbuffer<T>::const_iterator i, ie;

		for(i = cb.begin(), ie = cb.end(); i != ie; ++i) {
			os << *i << " ";
		}
		#ifndef NDEBUG
			os << "\nFinito di Stampare\n";
		#endif
		return os;
	}


	/**
		@brief Rispetta predicato

		La funzione verifica, per ogni elemento contenuto nel cbuffer, se esso rispetti o meno il predicato passato in input, e stampa a console il risultato.

		@param &cb cbuffer sui cui eementi richiamare il predicato.
		@param &pred predicato da applicare agli elementi del cbuffer.
	**/
	template<typename T, typename P>
	void evaluate_if(const cbuffer<T> &cb, const P &predicate) {

		//typename cbuffer<T>::const_iterator i, ie;
		//for(i=cb.begin(), ie=cb.end(); i!=ie; ++i) {
		for(int i=0; i<cb.getElements(); ++i){
			predicate(cb[i])
			? std::cout << "[" << i << "]: true." << std::endl
			: std::cout << "[" << i << "]: false." << std::endl;
		}
	}

#endif
