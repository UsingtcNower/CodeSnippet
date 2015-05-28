/*
 * 串口单例类
 * @auther: zhangt
 */
public class SerialPortFactory {
	private SerialPort mSerialPort = null;
	private SerialPortFinder mSerialPortFinder = new SerialPortFinder();
	
	/*
	 * 内部类实现单例模式
	 * 延迟加载，减少内存开销, 线程安全(java中class加载是互斥的)
	 */
	private static class SerialPortFactoryHolder {
		private static SerialPortFactory instance = new SerialPortFactory();
	}
	
	/*
	 * 私有构造函数
	 */
	private SerialPortFactory() {
		
	}
	
	public static SerialPortFactory getInstance() {
		return SerialPortFactoryHolder.instance;
	}
	
	public SerialPort getSerialPort() throws SecurityException, IOException, InvalidParameterException {
		if (mSerialPort == null) {
			/* Read serial port parameters */
			String path = getPath();
			int baudrate = getBaudrate();

			/* Check parameters */
			if ( (path.length() == 0) || (baudrate == -1)) {
				throw new InvalidParameterException();
			}

			/* Open the serial port */
			mSerialPort = new SerialPort(new File(path), baudrate, 0);
		}
		return mSerialPort;
	}

	public void closeSerialPort() {
		if (mSerialPort != null) {
			mSerialPort.close();
			mSerialPort = null;
		}
	}
}
