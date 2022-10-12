#pragma once

namespace be {

class Engine;

};

namespace be::input {

using Key = unsigned int;

class Keyboard {
public:
	static Keyboard &getInstance();

	bool isKeyPressed(Key key) const;
	bool isKeyDown(Key key) const;
	bool isKeyReleased(Key key) const;
private:
	friend class be::Engine;

	class KeyMap {
	public:
		KeyMap() = default;
		~KeyMap() = default;

		void operator=(const KeyMap &other);
		void insert(Key key);
		bool contains(Key key) const;
		void remove(Key key);
	private:
		static constexpr int CacheLineSize { 64 };
		static constexpr int ArraySize { (CacheLineSize - sizeof(unsigned char)) / sizeof(Key) / 2 };

		Key m_keys[ArraySize];
		unsigned char m_size { 0 };
	};
	Keyboard() = default;
	~Keyboard() = default;

	void update();

	void keyPressed(Key key);
	void keyReleased(Key key);

	KeyMap m_currFrameKeys;
	KeyMap m_oldFrameKeys;
};

}
